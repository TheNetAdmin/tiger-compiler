//
// Created by CHEGE on 2017/6/1.
//

#include "Temporary.h"

namespace Temporary
{
    int Temp::tempNum = 0;

    Temp::Temp()
    {
        tempName = "t" + tempNum;
        tempNum += 1;
    }

    const std::string Temp::getTempName() const
    {
        return tempName;
    }

    int Label::labelNum = 0;

    Label::Label()
    {
        labelName = "L" + labelNum;
        labelNum += 1;
    }

    Label::Label(const std::string &labelName) : labelName(labelName)
    {
    }

    const std::string Label::getLabelName() const
    {
        return labelName;
    }

    void Label::setLabelName(const std::string &labelName)
    {
        Label::labelName = labelName;
    }

    std::shared_ptr<Temp> makeTemp()
    {
        return std::make_shared<Temp>();
    }

    std::shared_ptr<Label> makeLabel()
    {
        return std::make_shared<Label>();
    }

    std::shared_ptr<Label> makeLabel(std::string &labelName)
    {
        return std::make_shared<Label>(labelName);
    }
}