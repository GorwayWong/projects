import yfinance as yf
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 参数设置
initial_cash = 10000  # 初始本金1万元
momentum_period = 126  # 6个月动量周期（约126个交易日）
threshold = 0.03  # 3%收益阈值

# 获取苹果公司股票数据（显式关闭自动调整）
data = yf.download('AAPL', start='2019-01-02', end='2024-10-30', auto_adjust=False)

# 如果返回的列是多重索引，则降为单层索引
if isinstance(data.columns, pd.MultiIndex):
    data.columns = data.columns.get_level_values(0)

# 处理列名问题
close_col = 'Adj Close' if 'Adj Close' in data.columns else 'Close'

# 计算时间序列动量
data['momentum'] = data[close_col].pct_change(periods=momentum_period)

# 生成交易信号（1:买入，0:卖出）
data['signal'] = np.where(data['momentum'] >= threshold, 1, 0)
data['signal'] = data['signal'].shift(1).fillna(0).astype(int)  # 转换为整型

# 提取2024年测试数据
test_data = data.loc['2024-01-02':].copy()
print(test_data.head())

# 初始化交易记录
cash = initial_cash
shares = 0
portfolio_values = []

# 执行交易策略（使用iterrows()遍历）
for date, row in test_data.iterrows():
    close_price = float(row[close_col])  # 转换为标量
    signal = int(row['signal'])           # 直接转换为整数

    # 执行买入信号
    if signal == 1 and cash > 0:
        shares = cash / close_price
        cash = 0

    # 执行卖出信号
    elif signal == 0 and shares > 0:
        cash = shares * close_price
        shares = 0

    # 记录当日资产总值
    portfolio_values.append(cash + shares * close_price)

# 计算买入持有策略（注意这里取第一个交易日的价格必须是标量）
buy_hold = initial_cash * (test_data[close_col].squeeze() / float(test_data[close_col].iloc[0]))

# 创建结果DataFrame
results = pd.DataFrame({
    'Momentum Strategy': portfolio_values,
    'Buy & Hold': buy_hold
}, index=test_data.index)

# 可视化结果对比
plt.figure(figsize=(12, 6))
plt.plot(results['Momentum Strategy'], label='动量策略', linewidth=2)
plt.plot(results['Buy & Hold'], label='长期持仓', linestyle='--')
plt.title('苹果股票交易策略对比（2024年）', fontsize=14)
plt.xlabel('日期', fontsize=12)
plt.ylabel('资产价值（美元）', fontsize=12)
plt.legend()
plt.grid(True)
plt.show()

# 输出关键指标
print("最终资产价值对比：")
print(f"动量策略: ${results['Momentum Strategy'].iloc[-1].item():.2f}")
print(f"长期持仓: ${results['Buy & Hold'].iloc[-1].item():.2f}")
print(f"\n策略收益率：")
print(f"动量策略: {(results['Momentum Strategy'].iloc[-1].item() / initial_cash - 1) * 100:.2f}%")
print(f"长期持仓: {(results['Buy & Hold'].iloc[-1].item() / initial_cash - 1) * 100:.2f}%")
