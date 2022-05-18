#include <iostream>
#include <string>

#include "../Src/MarkdownIndex.hpp"
#include "../Src/Slugger.hpp"


int main(int argc,char* argv[]){
    using md::Title;
    md::TitleList inList{Title{.level=1,.text="Gros fichier"},Title{.level=2,.text="Et un sous-titre ! -TEst## \"é\"<[0]>, est\'^ important & (pas_que) 10% pour20$*+10-\'3\'"},Title{.level=3,.text="Et un sous-sous titre"},Title{.level=3,.text="Parce qu'il faut bien plusieurs parties"},Title{.level=1,.text="?"},Title{.level=3,.text="Et un sous-sous titre"}};

    md::TitleList expected{Title{.level=1,.text="Gros fichier",.slug="gros-fichier"},Title{.level=2,.text="Et un sous-titre ! -TEst## \"é\"<[0]>, est\'^ important & (pas_que) 10% pour20$*+10-\'3\'",.slug="et-un-sous-titre---test-\"é\"0-est-important--pasque-10-pour2010-3"},Title{.level=3,.text="Et un sous-sous titre",.slug="et-un-sous-sous-titre"},Title{.level=3,.text="Parce qu'il faut bien plusieurs parties",.slug="parce-quil-faut-bien-plusieurs-parties"},Title{.level=1,.text="?",.slug=""},Title{.level=3,.text="Et un sous-sous titre",.slug="et-un-sous-sous-titre-1"}};

    auto slugCount{md::slugify(inList,md::slugify_github)};
    //-1 because the title "# ?" can not have a valid slug
    if(slugCount != size(inList)-1)
    {
        LOGEL("Slug count != title number in title list\nThis is not supposed to happen");
        LOGEL("Check titles and slug functions");
        for(const auto& e : inList)
        {
            if(empty(e.slug))
            {
                LOGEL("\tFound empty slug for title : <"<<e<<">");
            }
        }
        return 1;
    }

    //both lists (input & output) MUST have the same size
    bool failed{false};
    for(size_t i{}; i < size(inList);++i)
    {
        const auto& l{inList[i]};
        const auto& r{expected[i]};
        if(l.slug != r.slug)
        {
            failed = true;
            LOGEL("\tInvalid slug for <"<<l<<"> -- EXPECTED <"<<r<<">");
        }
        if(failed)
            return 1;
    }
    
    return 0;
}
