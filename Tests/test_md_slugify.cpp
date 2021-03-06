#include <iostream>
#include <string>

#define ENABLE_LOG

#include "../Src/MarkdownIndex.hpp"
#include "../Src/Slugger.hpp"

int main(int argc,char* argv[]){
    
    std::string input{"Et un sous-titre ! -TEst## \"é\"<[0]>, est\'^ important & (pas_que) 10% pour20$*+10-\'3\' ?"};
    std::string expected{"et-un-sous-titre---test-\"é\"0-est-important--pasque-10-pour2010-3-"};
    
    auto slug{md::slugify_github(input)};

    LOGEL("\nINP:"<<input<<"\nGOT:"<<slug<<"\nEXP:"<<expected<<"\n\n");
    if(slug != expected)
        return 1;

    input="Titre  ?";
    expected="titre--";
    slug = md::slugify_github(input);
    LOGEL("\nINP:"<<input<<"\nGOT:"<<slug<<"\nEXP:"<<expected);
    if(slug != expected)
        return 1;

    return 0;
}