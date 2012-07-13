#include "basic_data.h"


//====================================Group====================================

basic_data::Group::Group(const std::string& FileName):
	NowControlParty(0)
	{
	boost::property_tree::ptree ReadData;
	boost::property_tree::read_xml(FileName , ReadData );

    BOOST_FOREACH (const boost::property_tree::ptree::value_type& child, ReadData.get_child("Group.HavingItemList")) {
		auto value = boost::lexical_cast<std::string>(child.second.data());
		this->ItemBag.appendContent(value);
    }

	BOOST_FOREACH (const boost::property_tree::ptree::value_type& child, ReadData.get_child("Group.Party.Member")) {
		MemberList.push_back(std::shared_ptr<basic_data::Status>(new basic_data::Status(child)) );
	}

	PartyList.push_back(std::shared_ptr<basic_data::Party>(new basic_data::Party()));
	for(auto it=MemberList.begin();it!=MemberList.end();it++){
		PartyList.at(0)->appendMember(*it);
	}


}



basic_data::Group::Group(std::shared_ptr<Party>& p1){
	PartyList.push_back(p1);
}


item::ItemBag& basic_data::Group::getItemBag(){return ItemBag;}


const bool basic_data::Group::separateParty(){
	if (this->getPartyNum()==1){
		PartyList.push_back((PartyList.at(0))->separateParty());
		return true;
	}else{
		return false;
	}
	
}

const bool basic_data::Group::combineParty(){
	if (this->getPartyNum()==2){
		for(auto it = PartyList.at(1)->getMemberList().begin();it!=PartyList.at(1)->getMemberList().end();it++){
			PartyList.at(0)->appendMember(*it);
		}
		PartyList.pop_back();
		return true;
	}else{
		return false;
	}
	
}

void basic_data::Group::appendMember(std::shared_ptr<Person>& Member_){
	PartyList.at(0)->appendMember(Member_);
	MemberList.push_back(Member_);

}

const bool basic_data::Group::deleteMember(const std::string& Name){
	auto it=MemberList.begin();
	auto DeleteFlag=false;
	for(;it!=MemberList.end();it++){
		if ((*it)->getName()==Name){
			(*it)=nullptr;
			MemberList.erase(it);
			PartyList.at(0)->deleteMember(Name);
			DeleteFlag=true;
			break;
		}
	}

	return DeleteFlag;
}


const int basic_data::Group::getPartyNum()const{
	return PartyList.size();
}

const int basic_data::Group::getMemberNum() const{
	return MemberList.size();
}
 
const bool basic_data::Group::swapMember(const int a,const int b){
 	if ((a<0)||(a>3)) return false;
	if ((b<0)||(b>3)) return false;
	
	auto tmp= MemberList[a];
	MemberList[a]=MemberList[b];
	MemberList[b]=tmp;
	PartyList.at(0)->swapMember(a,b);

	return true;
}


//====================================Party====================================

basic_data::Party::Party(std::shared_ptr<Person>& p1){
	MemberList.push_back(p1);
}


basic_data::Party::Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2){
	MemberList.push_back(p1);
	MemberList.push_back(p2);

}

basic_data::Party::Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2, std::shared_ptr<Person>& p3){
	MemberList.push_back(p1);
	MemberList.push_back(p2);
	MemberList.push_back(p3);

}

basic_data::Party::Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2, std::shared_ptr<Person>& p3, std::shared_ptr<Person>& p4){
	MemberList.push_back(p1);
	MemberList.push_back(p2);
	MemberList.push_back(p3);
	MemberList.push_back(p4);
}

std::shared_ptr<basic_data::Party> basic_data::Party::separateParty(){
	
	auto tmp=std::shared_ptr<Party>();
	if (MemberList.size()==4){
		tmp = std::shared_ptr<Party>(new Party(MemberList.at(2),MemberList.at(3)));
		MemberList.pop_back();
		MemberList.pop_back();
	}

	return tmp;
}


void basic_data::Party::appendMember(std::shared_ptr<Person>& Member_){
	this->MemberList.push_back(Member_);
}

void basic_data::Party::deleteMember(const std::string& Name){
	for(auto it=MemberList.begin();it!=MemberList.end();it++){
		if ((*it)->getName()==Name){
			(*it)=nullptr;
			MemberList.erase(it);
			break;
		}
	}
}


std::vector<std::shared_ptr<basic_data::Person> >& basic_data::Party::getMemberList(){return MemberList;}


const int  basic_data::Party::getMemberNum() const{
	return MemberList.size();
}

const bool basic_data::Party::swapMember(const int a,const int b){
	if ((a<0)||(a>3)) return false;
	if ((b<0)||(b>3)) return false;
	
	auto tmp= MemberList[a];
	MemberList[a]=MemberList[b];
	MemberList[b]=tmp;
	
	return true;
}


//================================Status Methods================================
basic_data::Status::Status(const std::string& FileName,const std::string& Name_):
	EquipmentList(4)
	{

	for(auto i=0;i<4;i++){
		EquipmentList[i]=nullptr;
	}

	boost::property_tree::ptree ReadData;
	boost::property_tree::read_ini(FileName , ReadData );

	if (const auto value = ReadData.get_optional<std::string>(Name_+".Name")) {
		Name = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Lv")) {
		Lv = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".HP")) {
		HP = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".MP")) {
		MP = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".HPMax")) {
		HPMax = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".MPMax")) {
		MPMax = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Speed")) {
		Speed = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".AttackPoint")) {
		AttackPoint = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".DefensePoint")) {
		DefensePoint = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Intelligence")) {
		Intelligence = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".SpiritualStrength")) {
		SpiritualStrength = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Luck")) {
		Luck = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Class")) {
		Class = *value ;
	}

	if (const auto value = ReadData.get_optional<int>(Name_+".Species")) {
		Species = *value ;
	}



}

basic_data::Status::Status(const boost::property_tree::ptree::value_type& CharacterData):
	EquipmentList(4)
	{

	for(auto i=0;i<4;i++){
		EquipmentList[i]=std::shared_ptr<equipment::Equipment>();
	}


	if (const auto value =CharacterData.second.get_optional<std::string>("<xmlattr>.name")) {
		Name = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Lv")) {
		Lv = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("HP")) {
		HP = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("MP")) {
		MP = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("HPMax")) {
		HPMax = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("MPMax")) {
		MPMax = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Speed")) {
		Speed = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("AttackPoint")) {
		AttackPoint = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("DefensePoint")) {
		DefensePoint = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Intelligence")) {
		Intelligence = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("SpiritualStrength")) {
		SpiritualStrength = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Luck")) {
		Luck = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Class")) {
		Class = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<int>("Species")) {
		Species = *value ;
	}

	if (const auto value = CharacterData.second.get_optional<std::string>("Equipment.Weapon")) {
		if ((*value)!="NULL"){
			this->setEquipment(equipment::EquipmentDataBase::get(*value));
		}
	}
	if (const auto value = CharacterData.second.get_optional<std::string>("Equipment.Protection")) {
		if ((*value)!="NULL"){
			this->setEquipment(equipment::EquipmentDataBase::get(*value));
		}
	}
	if (const auto value = CharacterData.second.get_optional<std::string>("Equipment.Accessory")) {
		if ((*value)!="NULL"){
			this->setEquipment(equipment::EquipmentDataBase::get(*value));
		}
	}

	
	BOOST_FOREACH(const auto& MagicList,CharacterData.second.get_child("MagicList")) {
		
		if (const auto& MagicName=MagicList.second.get_value_optional<std::string>()){
			this->MagicList.push_back(magic::MagicDataBase::get(*MagicName));
		}
	}
	

}


std::shared_ptr<equipment::Equipment> basic_data::Status::getEquipment(const int ID) throw(std::out_of_range){
	if (ID<0) throw std::out_of_range("範囲外");
	if (ID>3) throw std::out_of_range("範囲外");

	return EquipmentList.at(ID);
}

std::shared_ptr<equipment::Equipment> basic_data::Status::changeEquipment(std::shared_ptr<equipment::Equipment>& SetEquipment){
	auto ReturnData=EquipmentList.at(SetEquipment->getType());
	EquipmentList[SetEquipment->getType()]=SetEquipment;
	return ReturnData;
}

std::shared_ptr<equipment::Equipment> basic_data::Status::removeEquipment(int ID) throw(std::out_of_range){
	if (ID<0) throw std::out_of_range("範囲外");
	if (ID>3) throw std::out_of_range("範囲外");
	auto ReturnData=EquipmentList.at(ID);
	EquipmentList[ID]=std::shared_ptr<equipment::Equipment>();
	return ReturnData;


}


std::deque<std::shared_ptr<magic::Magic> >& basic_data::Status::getMagicList(){return MagicList;}


const std::string basic_data::Status::getName() const {return Name;}

const int basic_data::Status::getLv() const {return Lv;}

const int basic_data::Status::getHP() const {return HP;}

const int basic_data::Status::getMP() const {return MP;}

const int basic_data::Status::getHPMax() const {return HPMax;}

const int basic_data::Status::getMPMax() const {return MPMax;}

const int basic_data::Status::getSpeed() const {return Speed;}

const int basic_data::Status::getAttackPoint() const {return AttackPoint;}

const int basic_data::Status::getDefensePoint() const {return DefensePoint;}

const int basic_data::Status::getIntelligence() const {return Intelligence;}

const int basic_data::Status::getSpiritualStrength() const {return SpiritualStrength;}

const int basic_data::Status::getLuck() const {return Luck;}

const int basic_data::Status::getClass() const {return Class;}

const int basic_data::Status::getSpecies() const {return Species;}



