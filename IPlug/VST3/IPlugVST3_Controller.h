#ifndef _IPLUGAPI_
#define _IPLUGAPI_

#undef stricmp
#undef strnicmp
#include "public.sdk/source/vst/vsteditcontroller.h"

#include "IPlugBase.h"

using namespace Steinberg;
using namespace Vst;

class IPlugVST3Controller : public EditControllerEx1
                          , public IMidiMapping
                          , public IPlugBase
{
public:
  struct IPlugInstanceInfo
  {
    Steinberg::FUID mOtherGUID;
  };
  
  IPlugVST3Controller(IPlugInstanceInfo instanceInfo, IPlugConfig c);
  virtual ~IPlugVST3Controller();

  // IEditController
  tresult PLUGIN_API initialize (FUnknown* context) override;
  IPlugView* PLUGIN_API createView (FIDString name) override;
  tresult PLUGIN_API setComponentState (IBStream* state) override; // receives the processor's state
  tresult PLUGIN_API setState (IBStream* state) override;
  tresult PLUGIN_API getState (IBStream* state) override;
  
  tresult PLUGIN_API setParamNormalized (ParamID tag, ParamValue value) override;
  ParamValue PLUGIN_API getParamNormalized(ParamID tag) override;
  ParamValue PLUGIN_API plainParamToNormalized(ParamID tag, ParamValue plainValue) override;
  ParamValue PLUGIN_API normalizedParamToPlain (ParamID tag, ParamValue valueNormalized) override;
  tresult PLUGIN_API getParamStringByValue (ParamID tag, ParamValue valueNormalized, String128 string) override;
  tresult PLUGIN_API getParamValueByString (ParamID tag, TChar* string, ParamValue& valueNormalized) override;

  //ComponentBase
  //tresult PLUGIN_API notify (IMessage* message) override {}

  //IMidiMapping
  tresult PLUGIN_API getMidiControllerAssignment(int32 busIndex, int16 channel, CtrlNumber midiControllerNumber, ParamID& tag) override;

  //IEditControllerEx
	tresult PLUGIN_API getProgramName (ProgramListID listId, int32 programIndex, String128 name /*out*/) override;
  
  DELEGATE_REFCOUNT (EditControllerEx1)
  tresult PLUGIN_API queryInterface (const char* iid, void** obj) override;
  
  //IPlugBase
  void BeginInformHostOfParamChange(int idx) override { beginEdit(idx); }
  void InformHostOfParamChange(int idx, double normalizedValue) override  { performEdit(idx, normalizedValue); }
  void EndInformHostOfParamChange(int idx) override  { endEdit(idx); }
  void InformHostOfProgramChange() override  { /* TODO: */}
  void ResizeGraphics() override { /* TODO: */ };
  
private:
  Vst::IComponentHandler* GetComponentHandler() { return componentHandler; }
  Steinberg::IPlugView* mView = nullptr;
  Steinberg::FUID mProcessorGUID;
};

IPlugVST3Controller* MakeController();

#endif // _IPLUGAPI_