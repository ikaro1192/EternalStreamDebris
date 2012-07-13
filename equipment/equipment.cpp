#include "equipment.h"

//=====================================Equipment=====================================
equipment::Equipment::Equipment(const std::string& Name_, const std::string& Explain_, const int Price_, const int Type_, const int UpHPMax_, const int UpMPMax_, const int UpSpeed_, const int UpAttackPoint_, const int UpDefensePoint_, const int UpIntelligence_, const int UpSpiritualStrength_, const int UpLuck_, const std::set<int>& ClassID_, const std::set<std::string>& CharcterName_):
	Name(Name_),
	Explain(Explain_),
	Price(Price_),
	Type(Type_),
	UpHPMax(UpHPMax_),
	UpMPMax(UpMPMax_),
	UpSpeed(UpSpeed_),
	UpAttackPoint(UpAttackPoint_),
	UpDefensePoint(UpDefensePoint_),
	UpIntelligence(UpIntelligence_),
	UpSpiritualStrength(UpSpiritualStrength_),
	UpLuck(UpLuck_),
	EquipableClass(ClassID_),
	EquipableCharacter(CharcterName_)
	{}


const std::string& equipment::Equipment::getName() const {return Name;}
const std::string& equipment::Equipment::getExplain() const{return Explain;}
const int equipment::Equipment::getType() const{return Type;}


const int equipment::Equipment::getUpHPMax() const{return UpHPMax;}

const int equipment::Equipment::getUpMPMax() const{return UpMPMax;}

const int equipment::Equipment::getUpSpeed() const{return UpSpeed;}

const int equipment::Equipment::getUpAttackPoint() const{return UpAttackPoint;}

const int equipment::Equipment::getUpDefensePoint() const{return UpDefensePoint;}

const int equipment::Equipment::getUpIntelligence() const{return UpIntelligence;}

const int equipment::Equipment::getUpSpiritualStrength() const{return UpSpiritualStrength;}

const int equipment::Equipment::getUpLuck() const{return UpLuck;}

const bool equipment::Equipment::checkEquipable(const int ClassID,const std::string& CharacterName,const int Type_)const{
	return (EquipableClass.count(ClassID)==1)&&(EquipableCharacter.count(CharacterName)==1)&&(Type==Type_);
}


//=================================EquipmentDataBaseImplementation=================================
equipment::EquipmentDataBaseImplementation::Content* equipment::EquipmentDataBaseImplementation::getContent(const boost::property_tree::ptree::value_type& child){

		if (auto& Name_ = child.second.get_optional<std::string>("<xmlattr>.name")){
		if (const auto& Explain_ = child.second.get_optional<std::string>("Explain")){
		if (const auto& Price_ = child.second.get_optional<int>("Price")){
		if (const auto& UpHPMax_ = child.second.get_optional<int>("UpHPMax")){
		if (const auto& UpMPMax_ = child.second.get_optional<int>("UpMPMax")){
		if (const auto& UpSpeed_ = child.second.get_optional<int>("UpSpeed")){
		if (const auto& UpAttackPoint_ = child.second.get_optional<int>("UpAttackPoint")){
		if (const auto& UpDefensePoint_ = child.second.get_optional<int>("UpDefensePoint")){
		if (const auto& UpIntelligence_ = child.second.get_optional<int>("UpIntelligence")){
		if (const auto& UpSpiritualStrength_ = child.second.get_optional<int>("UpSpiritualStrength")){
		if (const auto& UpLuck_ = child.second.get_optional<int>("UpLuck")){
		if (const auto& Type_ = child.second.get_optional<std::string>("Type")){
			std::set<int> EquipableClass_;
			std::set<std::string> EquipableCharacter_;
			BOOST_FOREACH(const auto& child2, child.second.get_child("EquipableClass")) {
				if (const auto& EquipableClassName_ = child2.second.get_value_optional<std::string>()){
					EquipableClass_.insert(basic_data::ClassName2ID(EquipableClassName_.get()));
				}
			}
			BOOST_FOREACH(const auto& child2, child.second.get_child("EquipableCharacter")) {
				if (const auto& EquipableCharacterName_ = child2.second.get_value_optional<std::string>()){
					EquipableCharacter_.insert(EquipableCharacterName_.get());
				}
			}

			return new Equipment(Name_.get(),Explain_.get(),Price_.get(),basic_data::EquipmentTypeName2ID(Type_.get()),UpHPMax_.get(),UpMPMax_.get(),UpSpeed_.get(),UpAttackPoint_.get(),UpDefensePoint_.get(),UpIntelligence_.get(),UpSpiritualStrength_.get(),UpLuck_.get(),EquipableClass_,EquipableCharacter_);
		}}}}}}}}}}}}
		return nullptr;
	}

const std::string equipment::EquipmentDataBaseImplementation::getRootName(){return "EquipmentList";}
const std::string equipment::EquipmentDataBaseImplementation::getFileName(){return "EquipmentDataBase.xml";}


//==================================HavingEquipment==================================

equipment::HavingEquipment::HavingEquipment(std::string EquipmentName):
	  bag::AbstructHavingObject<std::shared_ptr<Equipment>,9,HavingEquipment>(equipment::EquipmentDataBase::get(EquipmentName))
	{}

const std::string equipment::HavingEquipment::getName() const{return Self->getName();}
