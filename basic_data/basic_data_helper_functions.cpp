#include "basic_data_helper_functions.h"



const std::string basic_data::SpeciesID2Name(const int ID) throw(std::out_of_range){
	
	if (ID==0) return "��";
	if (ID==1) return "��";
	if (ID==2) return "��";
	if (ID==3) return "�y";
	if (ID==4) return "��";
	if (ID==5) return "��";
	
	throw std::out_of_range("�͈͊O");
	
}

const int basic_data::SpeciesName2ID(const std::string& Name) throw(std::out_of_range){
	
	if (Name=="��") return 0;
	if (Name=="��") return 1;
	if (Name=="��") return 2;
	if (Name=="�y") return 3;
	if (Name=="��") return 4;
	if (Name=="��") return 5;
	
	throw std::out_of_range("�͈͊O");
	
}

const std::string basic_data::ClassID2Name(const int ID){
	if (ID==0) return "Soldier";
	if (ID==1) return "Magician";
	if (ID==2) return "Archer";
	if (ID==3) return "Thief";

	throw std::out_of_range("�͈͊O");

}


const int basic_data::ClassName2ID(const std::string& Name){
	if (Name=="Soldier") return 0;
	if (Name=="Magician") return 1;
	if (Name=="Archer") return 2;
	if (Name=="Thief") return 3;

	throw std::out_of_range("�͈͊O");



}

const std::string EquipmentTypeID2Name(const int TypeID){
	if (TypeID==0) return "����";
	if (TypeID==1) return "�h��";
	if (TypeID==2) return "�A�N�Z�T��";

	throw std::out_of_range("�͈͊O");

}


const int basic_data::EquipmentTypeName2ID(const std::string& Name){
	if (Name=="����") return 0;
	if (Name=="�h��") return 1;
	if (Name=="�A�N�Z�T��") return 2;

	throw std::out_of_range("�͈͊O");



}
