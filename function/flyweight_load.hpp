/*******************************************************************************
                  DxLibの読み込み系の関数のFlyweightなラッパ

Copyright (C) 2011 つららソフト

作成者 いかろ、洲澤(HNあとで考えて)
動作環境VC++ 2008 Express Edition
作成日時 2011/02/19 17:31
最終更新 2011/02/19 17:31

<概要>
DxLibの読み込み関数系をFlyweightで扱えるようにしたファンクタ群です。

*******************************************************************************/


#include "DxLib.h"
#include<string>
#include<map>
#include <cassert>

#ifndef GARD_FLYWEIGHT_LOAD
#define GARD_FLYWEIGHT_LOAD

namespace function{


//================================FlyweightGraph================================
//LoadGraphをFlyweightで扱うためのクラス
//グラフィックハンドル=FlyweightGraph::Load("ファイル名");
class FlyweightGraph{
public:
	static int Load(std::string FileName);
	//グラフィックハンドルを削除する
	static void Delete(std::string FileName){DeleteGraph(getInstance().GrHwnd[FileName]);getInstance().GrHwnd.erase(FileName);};

private:
	std::map<std::string,int> GrHwnd;
	static FlyweightGraph& getInstance();
	
	FlyweightGraph(){}
    FlyweightGraph(const FlyweightGraph& rhs);
    FlyweightGraph& operator=(const FlyweightGraph& rhs);
};

class FlyweightSound{
public:
	// サウンドハンドルを取得する
	static int Load(std::string FileName);
	// サウンドハンドルを削除する
	static void Delete(std::string FileName){
		DeleteSoundMem(getInstance().SdHwnd[FileName]);
		getInstance().SdHwnd.erase(FileName);
	};


private:
	std::map<std::string,int> SdHwnd;
	static FlyweightSound& getInstance();

	FlyweightSound(){}
	FlyweightSound(const FlyweightSound& rhs);
	FlyweightSound& operator=(const FlyweightSound& rhs);

};

//===============================FlyweightDivGraph==============================
//LoadDivGraphをFlyweightで扱うためのクラス
//FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::Load("ファイル名",グラフィックHandleを格納するポインタ);
template<int AllNum,int XNum,int YNum,int XSize,int YSize>
class FlyweightDivGraph{
public:
	static void Load(std::string FileName,int *HandleBuf);
	~FlyweightDivGraph();

private:
	std::map<std::string,int*> GrHwnd;
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>& getInstance();

	
	FlyweightDivGraph(){}
    FlyweightDivGraph(const FlyweightDivGraph& rhs);
    FlyweightDivGraph& operator=(const FlyweightDivGraph& rhs);
};

//=================================FlyweightFont================================
//CreateFontToHandleをFlyweightで扱うためのクラス
//FlyweightDivGraph<Size,Thick,FontType>::Load("作成するフォント名");
template<int Size,int Thick,int FontType>
class FlyweightFont{
public:
	static int Load(std::string FontName);
	//NULLが渡されたときのためのオーバライド(char*でないのは解決が曖昧になるのを防ぐため)
	static int Load(int* FontName);
	~FlyweightFont(){}

private:
	std::map<std::string,int> FontHwnd;
	static FlyweightFont<Size,Thick,FontType>& getInstance();

	
	FlyweightFont(){}
    FlyweightFont(const FlyweightFont& rhs);
    FlyweightFont& operator=(const FlyweightFont& rhs);
};



}//functionの終わり



//=================================メソッド定義================================


//==============================FlyweightDivGraph==============================
template<int AllNum,int XNum,int YNum,int XSize,int YSize>
void function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::Load(std::string FileName,int *HandleBuf){
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize> &instance=getInstance();
    
	if (instance.GrHwnd.count(FileName)==0){
		int *GrBuf=new int[AllNum];//バッファ

		LoadDivGraph(FileName.c_str(),AllNum,XNum,YNum,XSize,YSize,GrBuf);
		instance.GrHwnd.insert( std::map<std::string,int*>::value_type(FileName,GrBuf));
	}
			
	int *TmpBuffer=instance.GrHwnd[FileName];//一時バッファ
	for(int i=0;i<AllNum;i++){
		HandleBuf[i]=TmpBuffer[i];
	}
		
	return;
}


template<int AllNum,int XNum,int YNum,int XSize,int YSize>
function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::~FlyweightDivGraph(){
	std::map<std::string,int*>::iterator it = GrHwnd.begin();
	while( it != GrHwnd.end() ){
		delete [] (*it).second;
		++it;
	}
	return;
}

template<int AllNum,int XNum,int YNum,int XSize,int YSize>
function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>& function::FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize>::getInstance(){
	static FlyweightDivGraph<AllNum,XNum,YNum,XSize,YSize> instance;
	return instance;
}

//=================================FlyweightFont================================
template<int Size,int Thick,int FontType>
int function::FlyweightFont<Size,Thick,FontType>::Load(std::string FontName){
    	FlyweightFont<Size,Thick,FontType> &instance=getInstance();

		if (instance.FontHwnd.count(FontName)==0){
			instance.FontHwnd.insert( std::map<std::string,int>::value_type(FontName,CreateFontToHandle(FontName.c_str(),Size,Thick,FontType)));
		}
    	return instance.FontHwnd[FontName];
}

template<int Size,int Thick,int FontType>
int function::FlyweightFont<Size,Thick,FontType>::Load(int* FontName){
		assert(FontName==NULL);
    	FlyweightFont<Size,Thick,FontType> &instance=getInstance();

		if (instance.FontHwnd.count("")==0){
			instance.FontHwnd.insert( std::map<std::string,int>::value_type("",CreateFontToHandle(NULL,Size,Thick,FontType)));
		}
    	return instance.FontHwnd[""];
}

template<int Size,int Thick,int FontType>
function::FlyweightFont<Size,Thick,FontType>& function::FlyweightFont<Size,Thick,FontType>::getInstance(){
	static function::FlyweightFont<Size,Thick,FontType> instance;
	return instance;
}

#endif
