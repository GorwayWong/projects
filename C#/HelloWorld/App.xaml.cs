using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace HelloWorld
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            Console.WriteLine("1.OnStartup被触发");
        }

        protected override void OnActivated(EventArgs e)
        {
            base.OnActivated(e);
            Console.WriteLine($"2.OnActivated被触发");
        }

        protected override void OnDeactivated(EventArgs e)
        {
            base.OnDeactivated(e);
            Console.WriteLine("3.OnDeactivated被触发");
        }

        protected override void OnExit(ExitEventArgs e)
        {
            base.OnExit(e);
            Console.WriteLine("4.OnExit被触发");
        }
    }
}
