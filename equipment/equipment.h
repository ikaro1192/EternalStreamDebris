#pragma once

#include <set>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "bag.hpp"
#include "effect_obj.h"
#include "container_database.hpp"
#include "basic_data_helper_functions.h"

namespace equipment{

//=====================================Equipment=====================================
class Equipment{
	public:

		//�R���X�g���N�^
		Equipment(const std::string& Name_, const std::string& Explain_, const int Price_, const int Type_, const int UpHPMax_, const int UpMPMax_, const int UpSpeed_, const int UpAttackPoint_, const int UpDefensePoint_, const int UpIntelligence_, const int UpSpiritualStrength_, const int UpLuck_, const std::set<int>& ClassID_, const std::set<std::string>& CharcterName_);

		const std::string& getName() const;
		const std::string& getExplain() const;
		const int getType() const;
		const unsigned int getPrice() const;


		//�e���ڂ̏㏸�l
		const int getUpHPMax() const;
		const int getUpMPMax() const;
		const int getUpSpeed() const;
		const int getUpAttackPoint() const;
		const int getUpDefensePoint() const;
		const int getUpIntelligence() const;
		const int getUpSpiritualStrength() const;
		const int getUpLuck() const;

		//�����\���ǂ�����Ԃ�
		const bool checkEquipable(const int ClassID,const std::string& CharacterName,const int Type_) const;

	private:
		const std::string Name;
		const std::string Explain;
		const unsigned int Price;

		//�㏸����l
		const int UpHPMax;
		const int UpMPMax;
		const int UpSpeed;
		const int UpAttackPoint;
		const int UpDefensePoint;
		const int UpIntelligence;
		const int UpSpiritualStrength;
		const int UpLuck;

		//�����̃^�C�v
		const int Type;

		//�����\�ȃN���X
		std::set<int> EquipableClass;
		//�����\�ȃL�����N�^
		std::set<std::string> EquipableCharacter;

};


//=================================EquipmentDataBaseImplementation=================================

//�����̃f�[�^�x�[�X�̎���
class EquipmentDataBaseImplementation: private boost::noncopyable{
	public:
		typedef Equipment Content;
		static  Content* getContent(const boost::property_tree::ptree::value_type& child);
		static const std::string getRootName();
		static const std::string getFileName();
};

//�ȒP�Ɉ�����悤�ɂ���typedef
typedef content_data_base::ContentDataBase<equipment::EquipmentDataBaseImplementation> EquipmentDataBase;


//==================================HavingEquipment==================================
//�o�b�O�̒��g
class HavingEquipment:public bag::AbstructHavingObject<std::shared_ptr<Equipment>,9,HavingEquipment>{
	public:
		HavingEquipment(std::string EquipmentName);

		effect_obj::EffectInterface* getEffect() const;
		const std::string getName() const;
		const std::string getExplain() const;
		const unsigned int getPrice() const;

};

//�ȒP�Ɉ�����悤�ɂ���typedef
typedef bag::ContentBag<equipment::HavingEquipment> EquipmentBag;

}//���O��ԏI���


