/*******************************************************************************
           効果を持つオブジェクトとその処理機構を扱うためのクラス群           
Copyright (C) 2012 つららソフト

作成者 いかろ
動作環境 VC++ 2010 Express Edition(C++11)
作成日時 2012/02/27 10:37
最終更新 2011/02/28 14:04

<概要>
アイテムや魔法など効果をユーザが選択した特定の対象に適応するような機構を提供する
クラス群です。

<クラス構成>
このクラス群はeffect_objという名前空間にまとめられ
説明だるいので以下割愛(後で直す)サンプル見れば分かると思う。

*******************************************************************************/

#pragma warning(disable:4290)
#pragma once

#include<string>
#include<vector>
#include<stdexcept>
#include<list>
#include<memory>
#include <boost/optional.hpp>


#include "AbstructLuaObject.hpp"
#include "effect_obj_support.h"

namespace effect_obj{

//===============================EffectInterface===============================
//※flyweightにするのでdeleteの必要なし
class EffectInterface{
	public:
		virtual const std::string getName() const = 0;
		virtual const std::string getType() const = 0;
		virtual lua_State* getScript() const = 0;
		virtual ~EffectInterface(){}
};



//================================EffectHandler================================
//適応対象を管理する。
//エフェクトとターゲットとのインターフェースとなる。
//TargetSetは操作対象(ターゲット)の集合
template<class TargetSet>
class EffectHandler : public EffectHandlerInterface{
	public:

		//EffectHandlerをManagerにappendするときにコンストラクタの引数としてターゲットの集合を渡す
		EffectHandler(TargetSet& TargetSet_);

		//以下はプログラマは意識する必要はない
		//ターゲットリストの取得
		std::vector<std::string> getTargetList(std::string EffectType);
		//ターゲットが死んでいたらfalseを返し、生きていたらエフェクトをターゲットに適応
		bool run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName);

	private:
		TargetSet& Target;
		std::vector<std::string> NULLVector;//ダミーの空のベクタ
};
/*TargetSetの暗黙のインターフェース
//操作対象になるターゲットの型
typedef Element
//Type名を返す
std::string getType();
//ターゲットになる一覧を返す(ターゲットが固定の場合は"NULL"が入ったstd::vectorを返す)
std::vector<std::string> getTargetList();
//指定された名前のターゲットの参照を返す
TargetSet::Element& getElement(std::string)
//指定された名前のターゲットが生きているかどうかを返す
bool getAliveFlag(std::string);

*/




//================================EffectManager================================
class EffectManager{
	public:

		//ターゲットを選択するための内部クラス
		class Selector;

		//コンストラクタ
		//引数は実行するLuaの関数名
		EffectManager(std::string RunFunctionName_):RunFunctionName(RunFunctionName_){}
		~EffectManager();

		//エフェクトハンドラの登録
		void appendHandler(EffectHandlerInterface* EffectHandler);

		//使用するエフェクトオブジェクトを受け取り、エフェクトのターゲットセレクタを返す
		//エフェクトオブジェクトが処理できない場合boost::noneを返す(つまり対応するエフェクトハンドラが存在しない)
		//ターゲットを選択する必要がない場合はnullptrが入る
		boost::optional<std::shared_ptr<Selector> > createEffectSelector(EffectInterface* Effect)throw(std::invalid_argument);


		
	private:
		//Effectはアイテム、Targetはその対象
		void set(Selector* ThisSelector,EffectInterface* SetEffect,std::string TargetName);
		std::vector<EffectHandlerInterface*> EffectSpecies;
		std::string RunFunctionName;

};

//EffectManagerの内部クラス
class EffectManager::Selector{
		public:
			
			//Selectorのイテレータ
			typedef std::vector<std::string>::iterator iterator;				
			iterator begin(){return TargetList.begin();}
			iterator end() {return TargetList.end();}
		
			//エフェクトを適応するターゲットを選択して発動
			void run(iterator Target);
			void run(std::string Target);
			void run(int Target);

			//EffectManagerから呼び出されるだけなのでプログラマは特に意識する必要はない
			Selector(std::vector<std::string>& TargetList_,EffectInterface* Effect_,EffectHandlerInterface* Handler_,EffectManager* Manager_);
			//デストラクタは何もしない
			~Selector(){}

			//ハンドラを返し、セレクタを消す
			static EffectHandlerInterface* GetHandler(EffectManager::Selector* Self);


		private:
			std::vector<std::string> TargetList;
			EffectManager* Manager;
			EffectInterface* Effect;
			EffectHandlerInterface* Handler;
			std::string TargetName;
	};


}//effect_obj名前空間終わり


//====================================method====================================
//EffectHandler
template<class TargetSet>
effect_obj::EffectHandler<TargetSet>::EffectHandler(TargetSet& TargetSet_):Target(TargetSet_),NULLVector(0){}

template<class TargetSet>
std::vector<std::string> effect_obj::EffectHandler<TargetSet>::getTargetList(std::string EffectType){
	if (Target.getType()==EffectType){
		return Target.getTargetList();
	}
	return NULLVector;
}

template<class TargetSet>
bool effect_obj::EffectHandler<TargetSet>::run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName){
	if (Target.getAliveFlag(TargetName) ){
		luabind::call_function<void>(Effect->getScript(),RunFunctionName.c_str(), boost::ref(Target.getElement(TargetName)));
		return true;
	}else{
		return false;
	}
}

