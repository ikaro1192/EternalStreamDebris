#include "DxLib.h"
#include<string>
#include<map>
#include "check_hitKey_moment_policy.hpp"

#ifndef GARD_FUNCTION
#define GARD_FUNCTION

namespace function{
template<int,typename> class CheckHitKeyMoment;
class NoarmalWait;//CheckHitKeyMomentのポリシー

//====================================limit====================================
//値の範囲を制限する為の関数
//丸めた値=limit(丸める値,下限,上限)
template<typename T>
const T& limit(const T& input,const T& lower,const T& uper);


//===========================CheckHitKeyMoment Method===========================
//CheckHitKeyを押した瞬間のみの判定にするクラス(ファンクタ)
//※ よく考えたらKeyIDで指定すると変更が困難...
//KeyIDはDxLibのCheckHitKeyの定数を参照
//WaitPolicyはカスタマイズする場合のポリシークラス(次までの間隔を決める等)
//	WaitPolicyの種類
//		NoarmalWait:一階押されたらはなされるまで検出しない
//		StepWait<int Step>:離されるか一定ステップたつまで検出しない
//		PretermitFewStepWait<int Step>:最初の数ステップは検出し、その後検出しない
//		TimeWait<int Time>:未実装
template<int KeyID,typename WaitPolicy=NoarmalWait>
class CheckHitKeyMoment{
public:
	CheckHitKeyMoment();
	bool operator()();
private:
	int KeyCounter;
	WaitPolicy WaitType;
};


//===============================ContentSelector===============================
//ダイアログなどの選択肢を扱いやすくするためのクラス
template<int LineNum,int ColumnNum=1,class SelectTypePolicy=void>
class ContentSelector{
	public:
		ContentSelector();
		int getSelectedID()const{return SelectedID;}
		void checkKey();
	private:
		CheckHitKeyMoment<KEY_INPUT_UP> UpKeyCheck; 
		CheckHitKeyMoment<KEY_INPUT_DOWN> DownKeyCheck; 
		CheckHitKeyMoment<KEY_INPUT_LEFT> LeftKeyCheck; 
		CheckHitKeyMoment<KEY_INPUT_RIGHT> RightKeyCheck;

		int SelectedID;//選択されている項目

};


}//functionの終わり



//=================================メソッド定義================================



//====================================limit====================================
template<typename T>
const T& function::limit(const T& input,const T& lower,const T& uper){
	if (input<lower)
		return lower;
	if (input>uper)
		return uper;
	return input;
}



//==============================CheckHitKeyMoment==============================
//コンストラクタ
template<int KeyID,typename WaitPolicy>
function::CheckHitKeyMoment<KeyID,WaitPolicy>::CheckHitKeyMoment(){
	KeyCounter=0;
}

//ファンクタとしてあつかうための()のオーバーロード
template<int KeyID,typename WaitPolicy>
bool function::CheckHitKeyMoment<KeyID,WaitPolicy>::operator ()(){
	if( CheckHitKey( KeyID ) == 1 ){
		if (KeyCounter==0){
			KeyCounter++;
			return true;
		}
		if (WaitType.check())return true;
	}else{
		if (KeyCounter>0){
			KeyCounter=0;
			WaitType.clear();
		}
	}
	return false;
}

//===============================ContentSelector===============================
template<int LineNum,int ColumnNum,class SelectTypePolicy>
function::ContentSelector<LineNum,ColumnNum,SelectTypePolicy>::ContentSelector():
	SelectedID(0){
	
	
	}

template<int LineNum,int ColumnNum,class SelectTypePolicy>
void function::ContentSelector<LineNum,ColumnNum,SelectTypePolicy>::checkKey(){
	if ( UpKeyCheck() ){
		SelectedID-=ColumnNum;
	}
	if ( DownKeyCheck() ){
		SelectedID+=ColumnNum;
	}
	if (ColumnNum!=0){
		if ( RightKeyCheck() ){
			SelectedID++;
		}
		if ( LeftKeyCheck() ){
			SelectedID--;
		}
	}
	SelectedID=(SelectedID%(LineNum*ColumnNum)+LineNum*ColumnNum)%(LineNum*ColumnNum);//関数化できそう。

}


#endif
