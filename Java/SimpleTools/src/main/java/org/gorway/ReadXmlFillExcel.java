package org.gorway;

import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Objects;

public class ReadXmlFillExcel {
    public static void main(String[] args) {
        String excelFilePath = "D:\\files\\tempFiles\\20250108-20250109TL2RMResult.xlsx"; // Excel 文件路径
        String xmlFolderPath = "D:\\files\\tempFiles\\MlSlPlateData"; // XML 文件夹路径
        try (FileInputStream excelFile = new FileInputStream(excelFilePath);
             Workbook workbook = new XSSFWorkbook(excelFile)) {

            Sheet sheet = workbook.getSheetAt(0); // 假设数据在第一个工作表
            int lastRowNum = sheet.getLastRowNum();

            for (int rowIndex = 1; rowIndex <= lastRowNum; rowIndex++) { // 从第二行开始（假设第一行为标题）
                Row row = sheet.getRow(rowIndex);
                if (row == null) continue;

                Cell plateIdCell = row.getCell(1); // B列
                if (plateIdCell == null) continue;

                String plateId = plateIdCell.getStringCellValue();
                String spare3Value = "";
                String datetimeValue = "";
                String spare2Value = "";

                // 在 XML 文件夹中查找对应的 XML 文件
                File xmlFolder = new File(xmlFolderPath);
                File[] xmlFiles = xmlFolder.listFiles((dir, name) -> name.toLowerCase().endsWith(".xml"));

                if (xmlFiles != null) {
                    for (File xmlFile : xmlFiles) {
                        if (matchesPlateId(xmlFile, plateId)) {
                            spare2Value = getXmlValue(xmlFile,"spare2");
                            if (Objects.equals(spare2Value, "1")){ // 取spare2标签为2的xml文件
                                spare3Value = getXmlValue(xmlFile, "spare3");
                                datetimeValue = getXmlValue(xmlFile, "datetime");
                                break; // 找到匹配的文件后可以退出循环
                            }
                        }
                    }
                }

                // 填充 P 列和 R 列
                Cell spare3Cell = row.createCell(15); // P列（索引15）
                spare3Cell.setCellValue(spare3Value);

                Cell datetimeCell = row.createCell(17); // R列（索引17）
                datetimeCell.setCellValue(datetimeValue);
            }

            // 将更改写入 Excel 文件
            try (FileOutputStream outputStream = new FileOutputStream(excelFilePath)) {
                workbook.write(outputStream);
            }

            System.out.println("更新完成！");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    // 检查 XML 文件中的 plateId 内容是否与给定的 plateId 匹配
    private static boolean matchesPlateId(File xmlFile, String plateId) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(xmlFile);
            NodeList plateIdNodes = document.getElementsByTagName("plateId");
            if (plateIdNodes.getLength() > 0) {
                String xmlPlateId = plateIdNodes.item(0).getTextContent();
                return xmlPlateId.equals(plateId);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    // 读取 XML 文件中指定标签的内容
    private static String getXmlValue(File xmlFile, String tagName) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(xmlFile);
            NodeList nodeList = document.getElementsByTagName(tagName);
            if (nodeList.getLength() > 0) {
                return nodeList.item(0).getTextContent();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }
}
