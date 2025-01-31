import re

# 提供测试用的字符串
response_text = '''jsonp_1645885800574_58482({
  "code": "402",
  "message": "活动现在挤不进去呀，待会再来试试吧"
});
'''

# 正则表达式
pattern = r'\{.*\}'

# 在字符串中搜索匹配的部分
json_data_match = re.search(pattern, response_text, re.DOTALL)

if json_data_match:
    json_data_str = json_data_match.group(1)
    print("成功匹配到的JSON数据部分为:")
    print(json_data_str)
else:
    print("未找到符合条件的JSON数据部分")