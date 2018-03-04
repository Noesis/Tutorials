using Noesis;

class View2: UserControl
{
    public DependencyProperty TextProperty = DependencyProperty.Register("Text", typeof(string),
        typeof(View2), new PropertyMetadata(""));

    public string Text
    {
        get { return (string)GetValue(TextProperty); }
        set { SetValue(TextProperty, value); }
    }
}