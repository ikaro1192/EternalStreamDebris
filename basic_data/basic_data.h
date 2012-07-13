#pragma once

#include <map>
#include <list>
#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include "effect_obj.h"
#include "item.h"
#include "bag.hpp"
#include "equipment.h"
#include "basic_data_helper_functions.h"
#include "magic.h"


namespace basic_data{

	
class Party;
class Group;
class Status;

//Maybe change later or not.
typedef Status Person;


//====================================Group====================================
class Group{
	public:

		//コンストラクタ
		Group(const std::string& FileName);
		Group(std::shared_ptr<Party>& p1);

		//デストラクタ
		~Group(){}

		//イテレータ系
		typedef std::deque<std::shared_ptr<Party> >::iterator PartyIterator;
		typedef std::vector<std::shared_ptr<Person> >::iterator MemberIterator;
		PartyIterator beginParty(){return PartyList.begin();}
		PartyIterator endParty(){return PartyList.begin();}
		MemberIterator beginMember(){return MemberList.begin();}
		MemberIterator endMember(){return MemberList.end();}


		//=====情報取得====

		//持っているお金
		const unsigned int getMoney()const{return Money;}
		//メンバの数
		const int getMemberNum()const;
		//パーティの数
		const int getPartyNum()const;

		//アイテムバッグの取得
		item::ItemBag& getItemBag();		
		//パーティーの操作
		//失敗したらfalseを返す
		void appendMember(std::shared_ptr<Person>& Member_);
		const bool deleteMember(const std::string& Name);
		const bool separateParty();
		const bool combineParty();
		
		const bool swapMember(const int a,const int b);

	private:
		unsigned int Money;
		item::ItemBag ItemBag;

		std::deque<std::shared_ptr<Party> > PartyList;
		std::vector<std::shared_ptr<Person> > MemberList;

		int NowControlParty;
};

//====================================Party====================================
class Party{
	public:
		Party(){}
		Party(std::shared_ptr<Person>& p1);
		Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2);
		Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2, std::shared_ptr<Person>& p3);
		Party(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2, std::shared_ptr<Person>& p3, std::shared_ptr<Person>& p4);

		void appendMember(std::shared_ptr<Person>& Member_);
		void deleteMember(const std::string& Name);
		const bool swapMember(const int a,const int b);
		const int getMemberNum() const;
		std::vector<std::shared_ptr<Person> >& getMemberList();
		std::shared_ptr<Party> separateParty();
	private:

		std::vector<std::shared_ptr<Person> > MemberList;

		int PositionX;
		int PositionY;
};


//====================================Status====================================
class Status{
	public:
		Status(const std::string& FileName,const std::string& Name_);
		Status(const boost::property_tree::ptree::value_type& CharacterData);

		const std::string getName() const;
		const int getLv() const;
		const int getHP() const;
		const int getMP() const;
		const int getHPMax() const;
		const int getMPMax() const;
		const int getSpeed() const;
		const int getAttackPoint() const;
		const int getDefensePoint() const;
		const int getIntelligence() const;
		const int getSpiritualStrength() const;
		const int getLuck() const;
		const int getClass() const;
		const int getSpecies() const;

		//持っている魔法オブジェクトへの参照を返す
		std::deque<std::shared_ptr<magic::Magic> >& getMagicList();

		//指定したID(装備の種類)の現在の装備を返す
		std::shared_ptr<equipment::Equipment> getEquipment(int ID) throw(std::out_of_range);
		//装備をはずす
		std::shared_ptr<equipment::Equipment> removeEquipment(int ID) throw(std::out_of_range);
		//装備を交換する(追加する装備の種類が現在未装備の場合Set)
		std::shared_ptr<equipment::Equipment> basic_data::Status::changeEquipment(std::shared_ptr<equipment::Equipment>& SetEquipment);
		//装備をセットする(changeEquipmentと同等)
		std::shared_ptr<equipment::Equipment> basic_data::Status::setEquipment(std::shared_ptr<equipment::Equipment>& SetEquipment){return this->changeEquipment(SetEquipment);}
	

	private:
		std::deque<std::shared_ptr<magic::Magic> > MagicList;
		std::vector<std::shared_ptr<equipment::Equipment> > EquipmentList;
		int HP;
		int MP;
		int HPMax;
		int MPMax;
		int Lv;//レベル
		int Speed;//すばやさ
		int AttackPoint;//物理攻撃力
		int DefensePoint;//物理防御力
		int Intelligence;//知力(魔法攻撃力)
		int SpiritualStrength;//精神力(魔法防御力)
		int Luck;//運
		int Class;//職業
		int Species;//属性
		int ExperiencePoint;//経験値
		std::string Name;//名前
		std::bitset<5> StateSberrance;//状態異常(未実装)
		
};


}//名前空間終わり
