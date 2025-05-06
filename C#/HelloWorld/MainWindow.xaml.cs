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

namespace HelloWorld
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            this.SourceInitialized += (s, e) => Console.WriteLine("1.MainWindow的SourceInitialized被执行");
            this.Activated += (s, e) => Console.WriteLine("2.MainWindow的Activated被执行");
            this.ContentRendered += (s, e) => Console.WriteLine("4.MainWindow的ContentRendered被执行");
            this.Deactivated += (s, e) => Console.WriteLine("5.MainWindow的Deactivated被执行");
            this.Closing += (s, e) => Console.WriteLine("6.MainWindow的Closing被执行");
            this.Closed += (s, e) => Console.WriteLine("7.MainWindow的Closed被执行");
            this.Unloaded += (s, e) => Console.WriteLine("8.MainWindow的Unloaded被执行");
        }
    }
}
