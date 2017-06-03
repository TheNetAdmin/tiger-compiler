//
// Created by CHEGE on 2017/6/1.
//

#ifndef SRC_TEMPLATE_H
#define SRC_TEMPLATE_H
#include <string>
#include <memory>

namespace Temporary{
    class Temp{
        std::string tempName;
    public:
        static int tempNum;
        Temp();

        const std::string getTempName() const;
    };

    class Label{
        std::string labelName;
    public:
        static int labelNum;
        Label();
        Label(const std::string &labelName);

        const std::string getLabelName() const;

        void setLabelName(const std::string &labelName);
    };

    std::shared_ptr<Temp> makeTemp();
    std::shared_ptr<Label> makeLabel();
    std::shared_ptr<Label> makeLabel(std::string &labelName);
}


#endif //SRC_TEMPLATE_H
