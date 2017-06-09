//
// Created by CHEGE on 2017/6/1.
//

#include "Temporary.h"
#include <sstream>

namespace Temporary
{
    int Temp::tempNum = 0;

    Temp::Temp()
    {
        std::stringstream ss;
        ss << tempNum;
        std::string tNum;
        ss >> tNum;
        tempName = "t" + tNum;
        tempNum += 1;
    }

    const std::string Temp::getTempName() const
    {
        return tempName;
    }

    int Label::labelNum = 0;

    Label::Label()
    {
        std::stringstream ss;
        ss << labelNum;
        std::string lNum;
        ss >> lNum;
        labelName = "L" + lNum;
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