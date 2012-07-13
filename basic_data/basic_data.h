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

		//�R���X�g���N�^
		Group(const std::string& FileName);
		Group(std::shared_ptr<Party>& p1);

		//�f�X�g���N�^
		~Group(){}

		//�C�e���[�^�n
		typedef std::deque<std::shared_ptr<Party> >::iterator PartyIterator;
		typedef std::vector<std::shared_ptr<Person> >::iterator MemberIterator;
		PartyIterator beginParty(){return PartyList.begin();}
		PartyIterator endParty(){return PartyList.begin();}
		MemberIterator beginMember(){return MemberList.begin();}
		MemberIterator endMember(){return MemberList.end();}


		//=====���擾====

		//�����Ă��邨��
		const unsigned int getMoney()const{return Money;}
		//�����o�̐�
		const int getMemberNum()const;
		//�p�[�e�B�̐�
		const int getPartyNum()const;

		//�A�C�e���o�b�O�̎擾
		item::ItemBag& getItemBag();		
		//�p�[�e�B�[�̑���
		//���s������false��Ԃ�
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

		//�����Ă��閂�@�I�u�W�F�N�g�ւ̎Q�Ƃ�Ԃ�
		std::deque<std::shared_ptr<magic::Magic> >& getMagicList();

		//�w�肵��ID(�����̎��)�̌��݂̑�����Ԃ�
		std::shared_ptr<equipment::Equipment> getEquipment(int ID) throw(std::out_of_range);
		//�������͂���
		std::shared_ptr<equipment::Equipment> removeEquipment(int ID) throw(std::out_of_range);
		//��������������(�ǉ����鑕���̎�ނ����ݖ������̏ꍇSet)
		std::shared_ptr<equipment::Equipment> basic_data::Status::changeEquipment(std::shared_ptr<equipment::Equipment>& SetEquipment);
		//�������Z�b�g����(changeEquipment�Ɠ���)
		std::shared_ptr<equipment::Equipment> basic_data::Status::setEquipment(std::shared_ptr<equipment::Equipment>& SetEquipment){return this->changeEquipment(SetEquipment);}
	

	private:
		std::deque<std::shared_ptr<magic::Magic> > MagicList;
		std::vector<std::shared_ptr<equipment::Equipment> > EquipmentList;
		int HP;
		int MP;
		int HPMax;
		int MPMax;
		int Lv;//���x��
		int Speed;//���΂₳
		int AttackPoint;//�����U����
		int DefensePoint;//�����h���
		int Intelligence;//�m��(���@�U����)
		int SpiritualStrength;//���_��(���@�h���)
		int Luck;//�^
		int Class;//�E��
		int Species;//����
		int ExperiencePoint;//�o���l
		std::string Name;//���O
		std::bitset<5> StateSberrance;//��Ԉُ�(������)
		
};


}//���O��ԏI���
