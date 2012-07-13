#include "basic_data_helper_functions.h"



const std::string basic_data::SpeciesID2Name(const int ID) throw(std::out_of_range){
	
	if (ID==0) return "風";
	if (ID==1) return "火";
	if (ID==2) return "水";
	if (ID==3) return "土";
	if (ID==4) return "光";
	if (ID==5) return "闇";
	
	throw std::out_of_range("範囲外");
	
}

const int basic_data::SpeciesName2ID(const std::string& Name) throw(std::out_of_range){
	
	if (Name=="風") return 0;
	if (Name=="火") return 1;
	if (Name=="水") return 2;
	if (Name=="土") return 3;
	if (Name=="光") return 4;
	if (Name=="闇") return 5;
	
	throw std::out_of_range("範囲外");
	
}

const std::string basic_data::ClassID2Name(const int ID){
	if (ID==0) return "Soldier";
	if (ID==1) return "Magician";
	if (ID==2) return "Archer";
	if (ID==3) return "Thief";

	throw std::out_of_range("範囲外");

}


const int basic_data::ClassName2ID(const std::string& Name){
	if (Name=="Soldier") return 0;
	if (Name=="Magician") return 1;
	if (Name=="Archer") return 2;
	if (Name=="Thief") return 3;

	throw std::out_of_range("範囲外");



}

const std::string EquipmentTypeID2Name(const int TypeID){
	if (TypeID==0) return "武器";
	if (TypeID==1) return "防具";
	if (TypeID==2) return "アクセサリ";

	throw std::out_of_range("範囲外");

}


const int basic_data::EquipmentTypeName2ID(const std::string& Name){
	if (Name=="武器") return 0;
	if (Name=="防具") return 1;
	if (Name=="アクセサリ") return 2;

	throw std::out_of_range("範囲外");



}
