

/*******************************************************************************
            状態遷移する(複合)オブジェクトを扱うためのフレームワーク

Copyright (C) 2012 つららソフト


作成者  いかろ
動作環境 VC++ 2010 Express Edition
作成日時 2011/08/21 10:37
最終更新 2012/06/5 21:17
安定版  2012/03/15 22:02
バージョン 1.01

 <更新履歴>
 ・2012/06/05 22:48
	バグ修正
 ・2012/05/18 21:08
    RunableComponentInterfaceのtypedefしSeenInterfaceにした(ソースコードの変更の必要なしだが、変更推奨)

 ・2012/03/29 13:20
	focusOnで引数を受け取れるようにインターフェース大幅修正

 ・2012/03/21 17:08
	defaltのfocusOnメソッドが呼ばれないバグを修正

 ・2012/03/15 22:02
	すべてのインターフェースクラスの
	void focusOn(TCommon& CommonData)
	メソッドを
	void focusOn(TCommon& CommonData)
	に変更。

<概要>
状態変化を伴うオブジェクト(戦闘やマップ、装備ダイアログあるいはシーンの遷移など)を
簡単にそして系統だって扱うためのフレームワークです。
主にRPGやSLG等での利用を想定しています。(あまり速度最適化は施していない)

<依存関係>
boost

<クラス構成>
このフレームワークはsto(StateTransitionObjectの略)という名前空間にまとめられ
SeenInterfaceクラス、RunablePieceInterfaceクラス、AbstructStoManagerクラスの3つの主要クラス
及びTManagerTypedefクラス,AbstructManagerの補助クラスからなります。 


SeenInterfaceクラス及びRunablePieceInterfaceクラスはシーンや状態を
可読性、修正しやすさを保ったまま表現するインターフェースを、
AbstructStoManagerクラスはそれらを扱う方法を提供します。
以降操作する側をマネージャ(AbstructStoManager)、操作される側(SeenInterface等)をオブジェクトと呼びます。

<クラスの動作及び相互作用>
・マネージャの動作
マネージャインスタンス化されるとAbstructStoManagerクラスのコンストラクタにより、初期化処理が行われる。

1.SeenInterfaceを操作する場合
	フォーカスの入っているオブジェクトのrunメソッドがマネージャにより呼ばれる。

2.MVCモデルによりRunablePieceInterfaceを操作する場合
	フォーカスの入っているオブジェクトのModelのinputメソッドがマネージャにより呼ばれる。
	↓
	すべてのModelのupdateメソッドがreferPriorityメソッドで設定された順に呼ばれる。
	↓
	すべてのViewのoutputメソッドが呼ばれ、フォーカスの入っているオブジェクトが返した返り値が外部に返される

3.RunablePieceInterfaceを操作する場合(非推奨)
	フォーカスの入っているオブジェクトのinputメソッドがマネージャにより呼ばれる。
	↓
	すべてのupdateメソッドがreferPriorityメソッドで設定された順に呼ばれる
	↓
	すべてのoutputメソッドが呼ばれ、フォーカスの入っているオブジェクトが返した返り値が外部に返される

のような動作を自動で行います。


<使い方>
1.RunableComponentInterface及びMVCAdaptor(あるいはRunablePieceInterface)から継承したクラスに具体的な内容を記述
2.扱いたいオブジェクトに対応したAbstructRunableComponentManager,AbstructMVCManager,AbstructRunablePieceManager
のどれかからから継承したManagerクラス(※1)のcreateメソッドを実装
(3.オプションでManagerの各読み込み処理を実装,必要ならばコンストラクタでinitメソッドを呼ぶ)
4.終了するまでManagerのrunを呼ぶ(ループで呼ぶことを想定)
というように一貫したものとなっています。

RunablePieceInterfaceをMVCモデルによって設計できるようなMVCAdaptorクラスがあります。
これを用いることによりRunablePieceInterfaceよりつよいMVCモデルで設計し保守性が向上します。
基本的にこちらを用いてください。
テンプレート引数はTResult,TCommonの他にModel<TResult,TCommon>とView<TResult,TCommon>があります。
ModelとViewを実装したクラスをテンプレート引数として渡すことにより自動的にRunablePieceInterfaceとして
扱えるクラスを返します。暗黙のインターフェースはヘッダ内部の詳細を見てください。

※1
テンプレートのTResult、TCommon、TObjTypeはそれぞれ
TResultにはManagerのrunの結果として返す型、
TCommonにはマネージャが持つオブジェクト同士の共有データの型、
TObjTypeはオブジェクト(RunablePieceInterface<TResult,TCommon>,あるいはRunableComponentInterface<TResult,TCommon>)
を指定する。

※2
MVCAdaptorのViewではTManagerをtypedefしたクラスであるTManagerTypedefを継承することを推奨します。


具体的な使用例はサンプルをご覧ください。

*******************************************************************************/

#include <stdlib.h>
#include <string>
#include <map>
#include <stdexcept>

#include<boost/any.hpp>
#include<boost/noncopyable.hpp>

#pragma warning(disable:4290)

#ifndef FRAMEWORK_STATE_TRANSITION_OBJECT
#define FRAMEWORK_STATE_TRANSITION_OBJECT

#ifdef _MSC_VER 
	#if _MSC_VER <1600
		#define nullptr NULL
	#endif
#endif

namespace sto{

template <class TResult,class TCommon> class RunableComponentInterface;
template <class TResult,class TCommon> class RunablePieceInterface;
template <class TResult,class TCommon,class TObjType> class AbstructManager;
template<typename TResult,typename TCommon,template<typename,typename>class Model,template<typename,typename>class View> class MVCAdaptor;
template<typename TResult,typename TCommon,template<typename,typename>class Objtype>class TManagerTypedef;


//===============================TManagerTypedef===============================
//サブクラスにTManagerへのtypedefを提供する
template<typename TResult,typename TCommon,template<typename,typename>class Objtype>
class TManagerTypedef{
protected:
	typedef sto::AbstructManager<TResult,TCommon,Objtype<TResult,TCommon> > TManager; 	
};

//================SeenInterface(RunableComponentInterface)=====================
//シーン等の独立度の高い単一オブジェクトを想定した比較的大きな実行単位のインターフェースクラス
template <class TResult,class TCommon> class RunableComponentInterface : public TManagerTypedef<TResult,TCommon,sto::RunableComponentInterface>{
public:
	//実行メソッド
	//フォーカスが入っているオブジェクトが呼ばれる
	virtual const TResult& run(TManager* Manager,TCommon& CommonData,std::map<std::string,boost::any>& ParameterList)=0;
	
	//フォーカスが移ったときに最初に呼ばれる
	virtual void focusOn(std::map<std::string,boost::any>& ParameterList)=0;
	//フォーカスが離れたときに呼ばれる
	virtual void focusOut()=0;
		
	//仮想デストラクタ
    virtual ~RunableComponentInterface(){}

};

//RunableComponentInterfaceのtypedef
template <class TResult,class TCommon> 
class SeenInterface :public RunableComponentInterface<TResult,TCommon>{};

//=========================RunablePieceInterface===============================
//複合オブジェクトの部品を想定した小さな実行単位のインターフェースクラス

template <class TResult,class TCommon> class RunablePieceInterface : public TManagerTypedef<TResult,TCommon,sto::RunablePieceInterface>{
public:
	//入力メソッド
	//キー入力で移動などに使用。
	//オブジェクトにフォーカスが入っているときのみ呼ばれる。
	virtual void input()=0;
	
	//状態維持メソッド
	//引数として共有データを受け取ることができる。
	//常に呼び出されオブジェクトの状態を変更,維持する。
	virtual void update(TCommon& CommonData)=0;
	
	//出力メソッド
	//引数としてマネージャのポインタを受け取り、マネージャのメソッドを呼ぶことができる。
	//内部データに基づき処理を行う。
	//内部状態を変化させることはできない。
	//常に呼び出され、フォーカスの入っているオブジェクトは返り値を環境に返すことができる。(フォーカスの入っていない場合、返り値は無視)
	virtual const TResult& output(TManager* Manager,std::map<std::string,boost::any>& ParameterList) const =0;

	//フォーカスが入ったときの処理を行う
	//他のオブジェクトから自分にフォーカスが移ったときに最初に呼ばれる
	virtual void focusOn(std::map<std::string,boost::any>& ParameterList)=0;
	//フォーカスが離れたときに呼ばれる
	virtual void focusOut()=0;
	
	//出力優先順位を返す関数
	//数値が大きいほどより後から出力される。範囲は任意。
	virtual int referPriority()=0;
	
	//仮想デストラクタ
    virtual ~RunablePieceInterface(){}

};

//MVCからRunablePieceInterfaceへのアダプタ
template<typename TResult,typename TCommon,template<typename,typename>class Model,template<typename,typename>class View>
class MVCAdaptor:public sto::RunablePieceInterface<TResult,TCommon>{
public:
	void input(){ModelObject.input();}
	void update(TCommon& CommonData){ModelObject.update(CommonData);}
	//インターフェースの都合上constにしてあるが、実質constメンバ関数でないようになっている。
	const TResult& output(TManager* Manager,std::map<std::string,boost::any>& ParameterList) const{return ViewObject.output(Manager,ParameterList,const_cast<const Model<TResult,TCommon>&>(ModelObject));}
	void focusOn(std::map<std::string,boost::any>& ParameterList){ModelObject.focusOn(ParameterList);ViewObject.focusOn(ParameterList);}
	void focusOut(){ModelObject.focusOut();ViewObject.focusOut();}
	int referPriority(){return ViewObject.referPriority();}
private:
	Model<TResult,TCommon> ModelObject;
	mutable View<TResult,TCommon> ViewObject;
};

/*
template<typename,typename>Modelの暗黙のインターフェース
	void input();
	void update(TCommon& CommonData);
	void focusOn(std::map<std::string,boost::any>& ParameterList);
	void focusOut();
template<typename,typename>Viewの暗黙のインターフェース
	TResult& output(TManager*,const Model<TResult,TCommon>&) const;
	void focusOn(CommonData);
	void focusOut();
	int referPriority();
*/



//=================================AbstructStoManager=====================================
//RunablePieceInterfaceおよびRunableComponentInterfaceを操作するための抽象クラス群
//実装詳細はAbstructManager

template<typename TResult,typename TCommon>
class AbstructRunableComponentManager:public AbstructManager<TResult,TCommon,sto::RunableComponentInterface<TResult,TCommon> >{};

template<typename TResult,typename TCommon>
class  AbstructSeenManager:public AbstructRunableComponentManager<TResult,TCommon>{};

template<typename TResult,typename TCommon>
class AbstructMVCManager:public AbstructManager<TResult,TCommon,sto::RunablePieceInterface<TResult,TCommon> >{};

template<typename TResult,typename TCommon>
class AbstructRunablePieceManager:public AbstructManager<TResult,TCommon,sto::RunablePieceInterface<TResult,TCommon> >{};






//AbstructStoManagerの内部実装詳細
template <class TResult,class TCommon,class TObjType> class AbstructManager : private boost::noncopyable{
public:
	//マネージャーを実行する
	const TResult& run();
	
	//フォーカスの入っているオブジェクト変更
	//変更できなければ例外送出
	//changeFocus(変更先オブジェクト名)
	void changeFocus(std::string ObjName)  throw(std::invalid_argument);

protected:

	AbstructManager();//デフォルトコンストラクタ
	AbstructManager(TCommon& CommonData_);//CommonDataを初期化するためのコンストラクタ

 	virtual ~AbstructManager();

	//初期化する
	//サブクラスのコンストラクタで呼ぶことを推奨(呼ばなくても一応は必要時に呼ばれるようになっている)
	void init();//初期化

	//オブジェクトをマネージャに追加
	//不正なオブジェクトを追加した場合例外送出
	//append(オブジェクト名、オブジェクトへのポインタ);
	//nameに"default"を指定すると自動的にそれが最初にフォーカスの入ったオブジェクトになる。
	//また、簡易ガーベージコレクタを実装しているため動的確保したポインタしか扱えない
	void append(std::string,TObjType*) throw(std::invalid_argument);

	/********************以下の関数はオーバーライドして使用********************/
	//マネージャにコンポジションするオブジェクトを生成、追加する(appendを利用)ファクトリメソッド。必須。
	virtual void create()=0;

	//以下はデータ読み込み系のオプションのメソッド(データのロードを局所化する)
	
	//データなどを読み込む処理を記述
	//どの読み込み処理よりも先に呼ばれる
	virtual void loadData(){}
	//画像を読み込む処理を記述
	virtual void loadImage(){}
	//サウンド関係を読み込む処理を記述
	virtual void loadSound(){}
	//フォントを読み込む処理を記述
	virtual void loadFont(){}


private:
						
	bool CreatedFlagOn;//マネージャの実体をCreateしたかのフラグ
	
	TCommon& CommonData;//共通データ
	TCommon DummyCommonData;//共通データ
	
	TResult& ResultData;//結果データ
	TResult DummyData;//ダミーデータ
	
	std::map<std::string,boost::any> ParameterList;//forcusOnに渡される引数

	std::map<std::string,TObjType*> ObjectMap;//オブジェクトの名前とポインタの連想配列 

	std::string SelectedObjectName;//現在選択されているオブジェクト名

	//runメソッドをパーツのタイプによって静的変更するための内部クラス
	template <class T,class S,class U>
	class RunFunction{
	public:
        static void run(AbstructManager<T,S,U>& Self){}
	};

};


}//名前空間の終わり


/*******************************************************************************
*                                                                              *
*                                メソッド定義部                                *
*                                                                              *
*******************************************************************************/


//============================defaultコンストラクタ=============================
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::AbstructManager():
	DummyData(),
	ResultData(DummyData),
	CommonData(DummyCommonData)
	{
	
	CreatedFlagOn=false;
	SelectedObjectName="default";

	
	}
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::AbstructManager(TCommon& CommonData_):
	DummyData(),
	ResultData(DummyData),
	CommonData(CommonData_)
	{
	
	CreatedFlagOn=false;
	SelectedObjectName="default";
	
	}



//===============================デストラクタ====================================
template <class TResult,class TCommon,class TObjType>
sto::AbstructManager<TResult,TCommon,TObjType>::~AbstructManager(){	
	{
		std::map<std::string,TObjType*>::iterator it = ObjectMap.begin();
		while( it != ObjectMap.end() ){
			delete((*it).second);
			(*it).second=nullptr;
			it++;
    	}
	}
	

}

//===================================init()======================================
//初期化
template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::init(){

	loadData();
	loadImage();
	loadSound();
	loadFont();
	create();
	CreatedFlagOn=true;	 
	ObjectMap[SelectedObjectName]->focusOn(ParameterList);

	}


//==================================append()======================================
template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::append(std::string ObjName,TObjType* AppendObj) throw(std::invalid_argument){
	ObjectMap.insert(std::map<std::string,TObjType*>::value_type(ObjName,AppendObj));
}



//=====================================changeFocus=================================


template <class TResult,class TCommon,class TObjType>
void sto::AbstructManager<TResult,TCommon,TObjType>::changeFocus(std::string ObjName) throw(std::invalid_argument){

	if (CreatedFlagOn==false){
		init();
	}

	if (ObjectMap.find(ObjName)==ObjectMap.end()) throw std::invalid_argument("指定した名前のオブジェクトが見つからない");
	
	ObjectMap[SelectedObjectName]->focusOut();
	SelectedObjectName=ObjName;
	ObjectMap[SelectedObjectName]->focusOn(ParameterList);
	
	
}

//=======================================run=======================================

template<class TResult,class TCommon,class TObjType>
const TResult& sto::AbstructManager<TResult,TCommon,TObjType>::run(){

	if (CreatedFlagOn==false){
		init();
	}

	//ParameterListを常に空に保つ
	if(!ParameterList.empty()) ParameterList.clear();

	RunFunction<TResult,TCommon,TObjType>::run(*this);


	return ResultData;
}

//===============================runの特殊化==================================

template<class TResult,class TCommon,class TObjType>
template <class T,class S>
class sto::AbstructManager<TResult,TCommon,TObjType>::RunFunction<T,S,sto::RunablePieceInterface<T,S> >{
public:
	static void run(AbstructManager<T,S,sto::RunablePieceInterface<T,S> >& Self){
	
		Self.ObjectMap[Self.SelectedObjectName]->input();//入力
	    

		//内容保持ブロック
		{
			unsigned int Counter=0;//表示したオブジェクトの数
			int NowDrawLevel=0;	
			
			while(Counter<Self.ObjectMap.size()){
				std::map<std::string,RunablePieceInterface<TResult,TCommon>*>::iterator it = Self.ObjectMap.begin();
					while( it != Self.ObjectMap.end() ){
						if ((((*it).second)->referPriority())==NowDrawLevel){
							((*it).second)->update(Self.CommonData);
							Counter++;
						}
						it++;
					}
				NowDrawLevel++;	
			}
		}
		
		//出力ブロック	
		{
			unsigned int Counter=0;//表示したオブジェクトの数
			int NowDrawLevel=0;	
			//出力
			Counter=0;
			NowDrawLevel=0;
			while(Counter<Self.ObjectMap.size()){
				std::map<std::string,RunablePieceInterface<TResult,TCommon>*>::iterator it = Self.ObjectMap.begin();
					while( it != Self.ObjectMap.end() ){
						if ((((*it).second)->referPriority())==NowDrawLevel){
							if ((*it).first==Self.SelectedObjectName){
								Self.ResultData=((*it).second)->output(&Self,Self.ParameterList);
							}else{
								((*it).second)->output(&Self,Self.ParameterList);
							}
							Counter++;
						}
						it++;
					}
				NowDrawLevel++;	
			}
		}
	}


};

template<class TResult,class TCommon,class TObjType>
template <class T,class S>
class sto::AbstructManager<TResult,TCommon,TObjType>::RunFunction<T,S,sto::RunableComponentInterface<T,S> >{
public:
	static void run(AbstructManager<T,S,sto::RunableComponentInterface<T,S> >& Self){
		Self.ResultData=Self.ObjectMap[Self.SelectedObjectName]->run(&Self,Self.CommonData,Self.ParameterList);
	}
};




#endif
