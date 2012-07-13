#pragma once
#pragma warning(disable:4290)

#include <string>
#include <stdexcept>

namespace basic_data{


//=================================Helperä÷êîåQ=================================
const std::string EquipmentTypeID2Name(const int TypeID);
const int EquipmentTypeName2ID(const std::string& Name);

const std::string SpeciesID2Name(const int ID) throw(std::out_of_range);
const int SpeciesName2ID(const std::string& Name) throw(std::out_of_range);

const std::string ClassID2Name(const int ID);
const int ClassName2ID(const std::string& ID);


}