

namespace effect_obj{
class EffectInterface;

//============================EffectHandlerInterface============================
//EffectHandlerをインターフェースとして扱うためのすりあわせとして存在するので
//これを継承して使うことは基本的にない。
class EffectHandlerInterface{
	public:
		//処理できないなら空のvectorを返す
		virtual std::vector<std::string> getTargetList(std::string EffectType) = 0;
		virtual bool run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName) = 0 ;
		virtual ~EffectHandlerInterface(){}
		
};

//=============================RunnableEffectTuple=============================
//実行可能な状態にあるエフェクトとターゲット、ハンドラの組(プログラマは意識する必要はない)
class RunnableEffectTuple{
	public:
		RunnableEffectTuple(EffectInterface* Effect_,std::string TargetName_,EffectHandlerInterface* Handler_);
		
		//特に仕事しない
		~RunnableEffectTuple(){}
			
		bool run(std::string RunFunctionName);
	
	private:
		EffectInterface* EffectObject;
		std::string TargetName;
		EffectHandlerInterface* Handler; 
};



}