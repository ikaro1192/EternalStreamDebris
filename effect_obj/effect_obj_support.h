

namespace effect_obj{
class EffectInterface;

//============================EffectHandlerInterface============================
//EffectHandler���C���^�[�t�F�[�X�Ƃ��Ĉ������߂̂��肠�킹�Ƃ��đ��݂���̂�
//������p�����Ďg�����Ƃ͊�{�I�ɂȂ��B
class EffectHandlerInterface{
	public:
		//�����ł��Ȃ��Ȃ���vector��Ԃ�
		virtual std::vector<std::string> getTargetList(std::string EffectType) = 0;
		virtual bool run(EffectInterface* Effect,std::string TargetName,std::string RunFunctionName) = 0 ;
		virtual ~EffectHandlerInterface(){}
		
};

//=============================RunnableEffectTuple=============================
//���s�\�ȏ�Ԃɂ���G�t�F�N�g�ƃ^�[�Q�b�g�A�n���h���̑g(�v���O���}�͈ӎ�����K�v�͂Ȃ�)
class RunnableEffectTuple{
	public:
		RunnableEffectTuple(EffectInterface* Effect_,std::string TargetName_,EffectHandlerInterface* Handler_);
		
		//���Ɏd�����Ȃ�
		~RunnableEffectTuple(){}
			
		bool run(std::string RunFunctionName);
	
	private:
		EffectInterface* EffectObject;
		std::string TargetName;
		EffectHandlerInterface* Handler; 
};



}