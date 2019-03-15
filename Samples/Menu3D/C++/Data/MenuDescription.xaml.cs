using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Menu3D
{
    /// <summary>
    /// Interaction logic for MenuDescription.xaml
    /// </summary>
    public partial class MenuDescription : UserControl
    {
        public MenuDescription()
        {
            InitializeComponent();
        }

        public string Description
        {
            get { return (string)GetValue(DescriptionProperty); }
            set { SetValue(DescriptionProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Description.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty DescriptionProperty = DependencyProperty.Register(
            "Description", typeof(string), typeof(MenuDescription), new PropertyMetadata(string.Empty));

        public string AcceptText
        {
            get { return (string)GetValue(AcceptTextProperty); }
            set { SetValue(AcceptTextProperty, value); }
        }

        // Using a DependencyProperty as the backing store for AcceptText.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty AcceptTextProperty = DependencyProperty.Register(
            "AcceptText", typeof(string), typeof(MenuDescription), new PropertyMetadata(string.Empty));

        public string CancelText
        {
            get { return (string)GetValue(CancelTextProperty); }
            set { SetValue(CancelTextProperty, value); }
        }

        // Using a DependencyProperty as the backing store for CancelText.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty CancelTextProperty = DependencyProperty.Register(
            "CancelText", typeof(string), typeof(MenuDescription), new PropertyMetadata(string.Empty));
    }
}
