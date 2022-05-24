#include <iostream>
#include <string>
#include <vector>


// #define ENABLE_LOG

#include "Src/MarkdownIndex.hpp"
#include "Src/LittleArgsParser/LittleArgsParser.hpp"

#include "Src/PerfTools/ScopeTimer.h"

#include <filesystem>

namespace
{

template<typename T>
std::ostream& operator<<(std::ostream& a,const std::vector<T>& arr){
    auto s{size(arr)};
    a<<"{";
    for(const auto& e : arr)
    {
        --s;
        a<<e;
        if(s != 0)
        {
            a<<",";
        }
    }
    a<<"}";
    return a;
}

std::string getHelp(const lap::CmdList& cmds){
    std::string description{"This program allows to auto generate markdown table of content\n"
                            "It lists all the titles found and link the TOC to them\n"
                            "The TOC will be placed between two tags in the markdown document :\n"
                            "\"<!--MARKDOWN_INDEX_BEGIN-->\" and \"<!--MARKDOWN_INDEX_END-->\"\n\n"
                            "Please note that you have to include these tags in your documents to mark the location of the TOC.\n\n"
                            "WARNING : everything between these tags will be removed on table generation\n\n"
                            "I strongly advise to run this program with the option \"-b\" to backup your files"};
    

    lap::helper::ExampleList ex{
        lap::helper::Example{.cliInput="MarkdownTable -bi MYFILE.md -o OUT.md",
        .description="First create a backup of <MYFILE.md> as <MYFILE.md.old>, then insert a table of content in it and saves it as <OUT.md>\nNote that MYFILE.md is never modified during the whole process"},
        lap::helper::Example{.cliInput="MarkdownTable -i MYFILE.md -b SECONDFILE.md",
        .description="First create a backup of <MYFILE.md> as <MYFILE.md.old> and <SECONDFILE.md> as <SECONDFILE.md.old>\nThen insert a table of content in both original files <MYFILE.md> and <SECONDFILE.md>"},
        lap::helper::Example{.cliInput="MarkdownTable -b MYFILE.md SECONDFILE.md --title \"** Table of Content **\"",
        .description="First create a backup of <MYFILE.md> as <MYFILE.md.old> and <SECONDFILE.md> as <SECONDFILE.md.old>\nThen insert a table of content in both original files <MYFILE.md> and <SECONDFILE.md> named \"** Table of Content **\""}
    };
    std::string helpMsg{lap::helper::getHelp(
        "MarkdownTable - Small program to auto-generate and insert in markdown files a table of content",
        description,
        cmds,
        ex
    )};
    return helpMsg;
}

} // namespace


int main(int argc,char* argv[]){

    lap::CmdList cmds{};

    auto cmd_backup = lap::addCommand(cmds,lap::Command{.shortCmd='b',.longCmd="backup",.argCount=0,.description=
                        "Backup each input file as <INPUT.old>"});
    auto cmd_input = lap::addCommand(cmds,lap::Command{.shortCmd='i',.longCmd="input",.argCount=1,.description=
                        "Specify explicitly an input file"});
    auto cmd_output = lap::addCommand(cmds,lap::Command{.shortCmd='o',.longCmd="output",.argCount=1,.description=
                        "Specify explicitly an output file. Note that this option can not be used if more than 1 input file is specified."});
    auto cmd_title = lap::addCommand(cmds,lap::Command{.shortCmd='t',.longCmd="title",.argCount=1,.description=
                        "Specify a title for the table of content. If not set, the default title will be used"});
    auto cmd_help = lap::addCommand(cmds,lap::Command{.shortCmd='h',.longCmd="help",.argCount=0,.description="Display this help"});

    auto parsedArgsOpt = lap::parseArgs(argc,argv,cmds);
    if(!parsedArgsOpt)
    {
        std::cerr << "An error occured when trying to parse command line arguments" <<"\n";
        return -1;
    }

    auto parsedArgs{parsedArgsOpt.value()};

    if(lap::matchedCmd(parsedArgs,cmd_help))
    {
        std::cout << getHelp(cmds)<<"\n";
        return 0;
    }

    lap::StringVector inputFiles{parsedArgs.freeArgs};

    auto match_backup{lap::matchedCmd(parsedArgs,cmd_backup)};
    auto match_input{lap::matchedCmd(parsedArgs,cmd_input)};
    auto match_output{lap::matchedCmd(parsedArgs,cmd_output)};
    auto match_title{lap::matchedCmd(parsedArgs,cmd_title)};


    if(match_input)
    {
        inputFiles.insert(end(inputFiles),cbegin(match_input.args),cend(match_input.args));
    }

    LOGL(inputFiles);

    if(size(inputFiles)==0)
    {
        std::cerr<<"Please specify at least one input file\nUse \"MarkdownTable --help\" to get more information"<<"\n";
        return -1;
    }
    
    if(match_output && size(inputFiles) != 1)
    {
        std::cerr<<"Invalid use of command <"<<lap::to_human(cmd_output)<<"> you can not use this option if you have more than 1 input file\nInput files list : "<<inputFiles<<"\n";
        return -1;
    }

    md::TableSettings tableSettings{.title="Table of content",.tabChar="&emsp;"};
    if(match_title)
    {
        //we have the guarantee to have 1 argument a specified by the command
        tableSettings.title = match_title.args[0];
    }

    for(const auto& file : inputFiles)
    {
        std::cout << "Processing -- "<<file<<" --"<<"\n";
        if(!std::filesystem::exists(file))
        {
            std::cout << "File not found : "<<file<<"\n";
            continue;
        }
        if(std::filesystem::is_directory(file))
        {
            std::cout << file<<" is a directory, please specify a file"<<"\n";
            continue;
        }

        if(match_backup)
        {
            auto backupFile{file+".old"};
            bool validBackup{true};
            try
            {
                validBackup = std::filesystem::copy_file(file,backupFile,std::filesystem::copy_options::overwrite_existing);
            }
            catch(const std::exception& e)
            {
                validBackup = false;
            }

            if(!validBackup)
            {
                std::cerr << "\tCannot make a backup of <"<<file<<"> as <"<<backupFile<<">"<<"\n";
                continue;
            }

            std::cout << "A backup of <"<<file<<"> was made as <"<<backupFile<<">"<<"\n";
        }

        //everything should be good
        //we have the guarantee that we'll have 1 argument for the output
        auto success{md::ram::insertTableInFile(file,(match_output)?match_output.args[0]:file,
                                                tableSettings)};

        if(!success)
        {
            std::cerr << "\tFAILURE : Cannot add index table to <"<<file<<">\n"
                  "Possible cause : you did not added the beginning and/or ending tag respectively :\n"
                  "\"<!--MARKDOWN_INDEX_BEGIN-->\" and \"<!--MARKDOWN_INDEX_END-->\""<<"\n";
            continue;
        }

        std::cout << "Successfully added table of content to "<<file<<"\n\n";
    }

    return 0;
}

/*
<!--MARKDOWN_INDEX_BEGIN-->
<!--MARKDOWN_INDEX_END-->
*/