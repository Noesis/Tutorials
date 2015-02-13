#include "pch.h"


using namespace Noesis;


NS_DECLARE_SYMBOL(Output)


////////////////////////////////////////////////////////////////////////////////////////////////////
class DelegateCommand: public BaseCommand
{
public:
    typedef Delegate<void (BaseComponent*)> Action;

    DelegateCommand(const Action& action): BaseCommand(NsSymbol::Null(), 0), _action(action) {}

    NsBool CanExecute(BaseComponent* param) const
    {
        return true;
    }

    void Execute(BaseComponent* param) const
    {
        _action(param);
    }

private:
    Action _action;

    NS_IMPLEMENT_INLINE_REFLECTION(DelegateCommand, BaseCommand)
    {
        NsMeta<TypeId>("DelegateCommand");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel: public BaseComponent, public INotifyPropertyChanged
{
public:
    ViewModel()
    {
        _command = *new DelegateCommand(MakeDelegate(this, &ViewModel::SayHello));
    }

    ~ViewModel()
    {
        _destroyed(this);
    }

    const NsChar* GetInput() const
    {
        return _input.c_str();
    }

    void SetInput(const NsChar* input)
    {
        _input = input;
    }

    const NsChar* GetOutput() const
    {
        return _output.c_str();
    }

    void SetOutput(const NsChar* output)
    {
        if (_output != output)
        {
            _output = output;
            _propertyChanged(this, NSS(Output));
        }
    }

    DelegateCommand* GetSayHelloCommand() const
    {
        return _command.GetPtr();
    }

    PropertyChangedEventHandler& PropertyChanged()
    {
        return _propertyChanged;
    }

    DestroyedEventHandler& Destroyed()
    {
        return _destroyed;
    }

    void Serialize(Noesis::Core::SerializationData* data) const
    {
        data->Serialize("Input", _input);
        data->Serialize("Output", _output);
    }

    void Unserialize(Noesis::Core::UnserializationData* data, NsUInt32 version)
    {
        data->Unserialize("Input", _input);
        data->Unserialize("Output", _output);
    }

private:
    void SayHello(BaseComponent* param)
    {
        if (Boxing::CanUnbox<NsString>(param))
        {
            char text[256];
            sprintf(text, "Hello, %s (%s)", _input.c_str(), Boxing::Unbox<NsString>(param).c_str());
            SetOutput(text);
        }
    }

private:
    Ptr<DelegateCommand> _command;

    NsString _input;
    NsString _output;

    PropertyChangedEventHandler _propertyChanged;
    DestroyedEventHandler _destroyed;

    NS_IMPLEMENT_INLINE_REFLECTION(ViewModel, BaseComponent)
    {
        NsMeta<TypeId>("Noesis.Samples.ViewModel");
        NsImpl<INotifyPropertyChanged>();

        NsProp("Input", &ViewModel::GetInput, &ViewModel::SetInput);
        NsProp("Output", &ViewModel::GetOutput, &ViewModel::SetOutput);
        NsProp("SayHelloCommand", &ViewModel::GetSayHelloCommand);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_DLL_EXPORT void NsRegisterReflection(ComponentFactory* factory, NsBool registerComponents)
{
    NS_REGISTER_COMPONENT(ViewModel)
}