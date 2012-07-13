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

		//コンストラクタ
		Equipment(const std::string& Name_, const std::string& Explain_, const int Price_, const int Type_, const int UpHPMax_, const int UpMPMax_, const int UpSpeed_, const int UpAttackPoint_, const int UpDefensePoint_, const int UpIntelligence_, const int UpSpiritualStrength_, const int UpLuck_, const std::set<int>& ClassID_, const std::set<std::string>& CharcterName_);

		const std::string& getName() const;
		const std::string& getExplain() const;
		const int getType() const;
		const unsigned int getPrice() const;


		//各項目の上昇値
		const int getUpHPMax() const;
		const int getUpMPMax() const;
		const int getUpSpeed() const;
		const int getUpAttackPoint() const;
		const int getUpDefensePoint() const;
		const int getUpIntelligence() const;
		const int getUpSpiritualStrength() const;
		const int getUpLuck() const;

		//装備可能かどうかを返す
		const bool checkEquipable(const int ClassID,const std::string& CharacterName,const int Type_) const;

	private:
		const std::string Name;
		const std::string Explain;
		const unsigned int Price;

		//上昇する値
		const int UpHPMax;
		const int UpMPMax;
		const int UpSpeed;
		const int UpAttackPoint;
		const int UpDefensePoint;
		const int UpIntelligence;
		const int UpSpiritualStrength;
		const int UpLuck;

		//装備のタイプ
		const int Type;

		//装備可能なクラス
		std::set<int> EquipableClass;
		//装備可能なキャラクタ
		std::set<std::string> EquipableCharacter;

};


//=================================EquipmentDataBaseImplementation=================================

//装備のデータベースの実装
class EquipmentDataBaseImplementation: private boost::noncopyable{
	public:
		typedef Equipment Content;
		static  Content* getContent(const boost::property_tree::ptree::value_type& child);
		static const std::string getRootName();
		static const std::string getFileName();
};

//簡単に扱えるようにするtypedef
typedef content_data_base::ContentDataBase<equipment::EquipmentDataBaseImplementation> EquipmentDataBase;


//==================================HavingEquipment==================================
//バッグの中身
class HavingEquipment:public bag::AbstructHavingObject<std::shared_ptr<Equipment>,9,HavingEquipment>{
	public:
		HavingEquipment(std::string EquipmentName);

		effect_obj::EffectInterface* getEffect() const;
		const std::string getName() const;
		const std::string getExplain() const;
		const unsigned int getPrice() const;

};

//簡単に扱えるようにするtypedef
typedef bag::ContentBag<equipment::HavingEquipment> EquipmentBag;

}//名前空間終わり


