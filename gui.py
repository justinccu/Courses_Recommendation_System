from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QListWidget, QMessageBox, QApplication, QWidget, QPushButton, QLabel
import subprocess
from PyQt5.QtGui import QFont, QPixmap
import sys
import numpy as np
from gensim.models import Word2Vec

data = []

class Ui_Form(object):
    def setupUi(self, Form):
        # 載入 word2vec
        print("載入 word2vec.model ...")
        self.model = Word2Vec.load('word2vec.model')
        print("載入完成！")

        Form.setObjectName("Form")
        Form.resize(818, 500)

        self.plainTextEdit = QtWidgets.QPlainTextEdit(Form)
        self.plainTextEdit.setGeometry(QtCore.QRect(100, 30, 211, 31))
        self.plainTextEdit.setObjectName("plainTextEdit")

        self.listwidget = QListWidget(Form)
        self.listwidget.setGeometry(QtCore.QRect(20, 80, 291, 331))
        self.listwidget.setObjectName("listWidget")

        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(20, 40, 71, 16))
        self.label.setObjectName("label")

        self.textBrowser = QtWidgets.QTextBrowser(Form)
        self.textBrowser.setGeometry(QtCore.QRect(350, 70, 401, 361))
        self.textBrowser.setObjectName("textBrowser")

        self.widget = QtWidgets.QWidget(Form)
        self.widget.setGeometry(QtCore.QRect(340, 30, 361, 25))
        self.widget.setObjectName("widget")

        self.horizontalLayout = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setSpacing(5)
        self.horizontalLayout.setObjectName("horizontalLayout")

        self.button_0 = QtWidgets.QPushButton(Form)
        self.button_0.setGeometry(QtCore.QRect(450, 450, 225, 25))
        self.button_0.setObjectName("button_0")

        self.button = QtWidgets.QPushButton(self.widget)
        self.button.setObjectName("button")
        self.horizontalLayout.addWidget(self.button)

        self.button_2 = QtWidgets.QPushButton(self.widget)
        self.button_2.setObjectName("button_2")
        self.horizontalLayout.addWidget(self.button_2)

        self.button_3 = QtWidgets.QPushButton(self.widget)
        self.button_3.setObjectName("button_3")
        self.horizontalLayout.addWidget(self.button_3)

        self.button_4 = QtWidgets.QPushButton(self.widget)
        self.button_4.setObjectName("button_4")
        self.horizontalLayout.addWidget(self.button_4)

        self.button_6 = QtWidgets.QPushButton(self.widget)
        self.button_6.setObjectName("button_6")
        self.horizontalLayout.addWidget(self.button_6)

        self.widget1 = QtWidgets.QWidget(Form)
        self.widget1.setGeometry(QtCore.QRect(60, 430, 201, 25))
        self.widget1.setObjectName("widget1")

        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.widget1)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")

        self.button_5 = QtWidgets.QPushButton(self.widget1)
        self.button_5.setObjectName("button_5")
        self.horizontalLayout_2.addWidget(self.button_5)

        self.button_7 = QtWidgets.QPushButton(self.widget1)
        self.button_7.setObjectName("button_7")
        self.horizontalLayout_2.addWidget(self.button_7)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def generate_list_items(self, output):
        self.listwidget.clear()
        if output == '-1':
            QMessageBox.information(None, "提示", "找不到課程")
        else:
            outputs = output.split('\n')
            dictionary = {}
            i = 0
            data.clear()
            for item in outputs:
                if item.strip():
                    dictionary[f"key{i+1}"] = item
                    i += 1
                    if i == 11:
                        data.append(dictionary.copy())
                        dictionary = {}
                        i = 0
            for x in data:
                value1 = QtWidgets.QListWidgetItem(x.get("key5")).text()
                value2 = QtWidgets.QListWidgetItem(x.get("key4")).text()
                value3 = QtWidgets.QListWidgetItem(x.get("key3")).text()
                temp1 = value1.split(":", 1)
                temp2 = value2.split(":")
                temp3 = value3.split(":")
                listItem = temp1[1].strip() + "/" + temp3[1].strip() + "/" + temp2[1].strip()
                self.listwidget.addItem(listItem)
        if self.listwidget.count() > 0:
            self.listwidget.setCurrentRow(0)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Course selection assistance system"))
        self.label.setText(_translate("Form", "在此輸入:"))
        self.button.setText("搜尋課程")
        self.button.clicked.connect(self.run_searching)
        self.button_2.setText("推薦課程")
        self.button_2.clicked.connect(self.run_recommand)
        self.button_3.setText("預覽課表")
        self.button_3.clicked.connect(self.run_classtable)
        self.button_4.setText("匯出課表")
        self.button_4.clicked.connect(self.run_exportfile)
        self.button_5.setText("加入選課")
        self.button_5.clicked.connect(self.run_addclass)
        self.button_0.setText("結束選課")
        self.button_0.clicked.connect(self.exit_sys)
        self.button_6.setText("列出課程")
        self.button_6.clicked.connect(self.run_listclass)
        self.button_7.setText("刪除課程")
        self.button_7.clicked.connect(self.run_deleteclass)

        self.listwidget.itemClicked.connect(self.show_selected_item)
        self.second_window = SecondWindow()

    def run_deleteclass(self):
        selected_item = self.listwidget.currentItem()
        if not selected_item:
            QMessageBox.information(None, "提示", "請先選擇一項")
            return
        selected_text = selected_item.text()
        split_text = selected_text.split("/")
        value1 = split_text[0].strip()
        value2 = split_text[2].strip()
        value3 = split_text[1].strip()
        for x in data:
            if ("Course Title: "+value1 == x.get("key5")) and ("Class Type: "+value2 == x.get("key4")) and ("Course ID: "+value3 == x.get("key3")):
                a = x.get("key3")
                split_key1 = a.split(":")
                result = subprocess.run(
                    ["./test.out", "6", split_key1[1], value2], capture_output=True, text=True)
                output = result.stdout.strip()
                QMessageBox.information(None, "提示", output)
        self.run_listclass()

    def run_listclass(self):
        result = subprocess.run(["./test.out", "5"], capture_output=True, text=True)
        output = result.stdout
        data.clear()
        self.generate_list_items(output)

    def exit_sys(self):
        sys.exit()

    def run_recommand(self):
        # 轉換課程向量
        course_vector = np.zeros(100)
        i = 0
        with open('out.txt', 'r') as f:
            for line in f:
                words = line.strip().split()
                total_vectors = np.zeros(100)
                for word in words:
                    try:
                        vector = self.model.wv.get_vector(word)
                        total_vectors += vector
                    except KeyError:
                        continue
                course_vector = np.vstack((course_vector, total_vectors))
                i += 1
        word_vectors = np.zeros(100)
        line = self.plainTextEdit.toPlainText()
        words = line.split()
        for word in words:
            try:
                vector = self.model.wv.get_vector(word)
                word_vectors += vector
            except KeyError:
                continue

        array = ""
        course_count = 0
        for i in range(1, len(course_vector)):
            if (np.linalg.norm(word_vectors) == 0):
                continue
            if (np.linalg.norm(course_vector[i]) == 0):
                continue
            w2v_similarity = np.dot(word_vectors, course_vector[i]) / (
                np.linalg.norm(word_vectors) * np.linalg.norm(course_vector[i]))
            if w2v_similarity >= 0.60:
                array = array + str(i-1) + ' ' + str(w2v_similarity) + ' '
                course_count += 1

        result = subprocess.run(
            ["./test.out", "4", str(course_count), array], capture_output=True, text=True)
        output = result.stdout
        data.clear()
        self.generate_list_items(output)

    def run_classtable(self):
        self.second_window = SecondWindow()
        self.second_window.show()

    def run_exportfile(self):
        self.b_instance = SecondWindow()
        self.b_instance.grab_screenshot()

    def run_addclass(self):
        selected_item = self.listwidget.currentItem()
        if selected_item is None:
            QMessageBox.information(None, "提示", "請先選擇一項")
            return
        selected_text = selected_item.text()
        self.textBrowser.clear()
        split_text = selected_text.split("/")
        value1 = split_text[0].strip()
        value2 = split_text[2].strip()
        value3 = split_text[1].strip()
        for x in data:
            if ("Course Title: "+value1 == x.get("key5")) and ("Class Type: "+value2 == x.get("key4")) and ("Course ID: "+value3 == x.get("key3")):
                a = x.get("key3")
                split_key1 = a.split(":")
                b = x.get("key4")
                split_key2 = b.split(":")
                c = x.get("key6")
                split_key4 = c.split(": ")
                result = subprocess.run(
                    ["./test.out", "2", split_key1[1], split_key2[1], split_key4[1]], capture_output=True, text=True)
                output = result.stdout.strip()
                QMessageBox.information(None, "提示", output)

    def run_searching(self):
        input_text = self.plainTextEdit.toPlainText()
        result = subprocess.run(["./test.out", "1", input_text], capture_output=True, text=True)
        output = result.stdout
        data.clear()
        self.generate_list_items(output)

    def show_selected_item(self):
        selected_item = self.listwidget.currentItem()
        if selected_item:
            selected_text = selected_item.text()
            self.textBrowser.clear()
            split_text = selected_text.split("/")
            value1 = split_text[0].strip()
            value2 = split_text[1].strip()
            value3 = split_text[2].strip()
            for x in data:
                if ("Course Title: "+value1 == x.get("key5")) and ("Class Type: "+value3 == x.get("key4")) and ("Course ID: "+value2 == x.get("key3")):
                    for key, value in x.items():
                        font = QFont()
                        font.setPointSize(13)
                        self.textBrowser.setFont(font)
                        self.textBrowser.append(f"{value}\n")

class SecondWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('預覽課表')
        self.setGeometry(700, 150, 700, 700)

        # 25格
        self.display_labels = {}
        self.display_labels["Mon_AB"] = QLabel(self)
        self.display_labels["Mon_CD"] = QLabel(self)
        self.display_labels["Mon_EF"] = QLabel(self)
        self.display_labels["Mon_GH"] = QLabel(self)
        self.display_labels["Mon_IJ"] = QLabel(self)
        self.display_labels["Tue_AB"] = QLabel(self)
        self.display_labels["Tue_CD"] = QLabel(self)
        self.display_labels["Tue_EF"] = QLabel(self)
        self.display_labels["Tue_GH"] = QLabel(self)
        self.display_labels["Tue_IJ"] = QLabel(self)
        self.display_labels["Wed_AB"] = QLabel(self)
        self.display_labels["Wed_CD"] = QLabel(self)
        self.display_labels["Wed_EF"] = QLabel(self)
        self.display_labels["Wed_GH"] = QLabel(self)
        self.display_labels["Wed_IJ"] = QLabel(self)
        self.display_labels["Thu_AB"] = QLabel(self)
        self.display_labels["Thu_CD"] = QLabel(self)
        self.display_labels["Thu_EF"] = QLabel(self)
        self.display_labels["Thu_GH"] = QLabel(self)
        self.display_labels["Thu_IJ"] = QLabel(self)
        self.display_labels["Fri_AB"] = QLabel(self)
        self.display_labels["Fri_CD"] = QLabel(self)
        self.display_labels["Fri_EF"] = QLabel(self)
        self.display_labels["Fri_GH"] = QLabel(self)
        self.display_labels["Fri_IJ"] = QLabel(self)

        # 設定正確 geometry，否則 QLabel 疊在一起
        self.display_labels["Mon_AB"].setGeometry(97, 47, 138, 127)
        self.display_labels["Mon_CD"].setGeometry(97, 178, 138, 127)
        self.display_labels["Mon_EF"].setGeometry(97, 310, 138, 127)
        self.display_labels["Mon_GH"].setGeometry(97, 441, 138, 127)
        self.display_labels["Mon_IJ"].setGeometry(97, 572, 138, 127)

        self.display_labels["Tue_AB"].setGeometry(240, 47, 102, 127)
        self.display_labels["Tue_CD"].setGeometry(240, 178, 102, 127)
        self.display_labels["Tue_EF"].setGeometry(240, 310, 102, 127)
        self.display_labels["Tue_GH"].setGeometry(240, 441, 102, 127)
        self.display_labels["Tue_IJ"].setGeometry(240, 572, 102, 127)

        self.display_labels["Wed_AB"].setGeometry(346, 45, 120, 129)
        self.display_labels["Wed_CD"].setGeometry(346, 178, 120, 129)
        self.display_labels["Wed_EF"].setGeometry(346, 310, 120, 129)
        self.display_labels["Wed_GH"].setGeometry(346, 441, 120, 129)
        self.display_labels["Wed_IJ"].setGeometry(346, 572, 120, 129)

        self.display_labels["Thu_AB"].setGeometry(469, 45, 104, 129)
        self.display_labels["Thu_CD"].setGeometry(469, 178, 104, 129)
        self.display_labels["Thu_EF"].setGeometry(469, 310, 104, 129)
        self.display_labels["Thu_GH"].setGeometry(469, 441, 104, 129)
        self.display_labels["Thu_IJ"].setGeometry(469, 572, 104, 129)

        self.display_labels["Fri_AB"].setGeometry(576, 45, 120, 130)
        self.display_labels["Fri_CD"].setGeometry(576, 178, 120, 130)
        self.display_labels["Fri_EF"].setGeometry(576, 310, 120, 130)
        self.display_labels["Fri_GH"].setGeometry(576, 441, 120, 130)
        self.display_labels["Fri_IJ"].setGeometry(576, 572, 120, 130)
    

        # 批次 style 設定
        for label in self.display_labels.values():
            label.setStyleSheet('background-color: rgba(255, 255, 255, 0.5);')
            label.setWordWrap(True)
            label.setFont(QtGui.QFont("Arial", 10))
            label.setText("")
            label.raise_()

        # 背景圖要最後建
        self.background_label = QLabel(self)
        self.background_label.setGeometry(self.rect())
        pixmap = QPixmap('time_table.jpg')
        self.background_label.setPixmap(pixmap)
        self.background_label.setScaledContents(True)
        self.background_label.lower()

        # 讀課表
        result = subprocess.run(["./test.out", "3"], capture_output=True, text=True)
        output = result.stdout.strip()
        lines = [line for line in output.split("\n") if line.strip() != ""]
        for i in range(0, len(lines), 2):
            if i+1 >= len(lines): continue
            course = lines[i]
            time_str = lines[i+1]
            if '.' not in time_str: continue
            day, periods = time_str.split('.', 1)
            periods_list = periods.split(',')
            for p in periods_list:
                session = p.strip()
                txt = course + '(' + session + ')'
                if session in ["1", "2", "3", "A", "B"]:
                    slot = "AB"
                elif session in ["4", "5", "6", "C", "D"]:
                    slot = "CD"
                elif session in ["7", "8", "9", "E", "F"]:
                    slot = "EF"
                elif session in ["10", "11", "12", "G", "H"]:
                    slot = "GH"
                elif session in ["13", "14", "15", "I", "J"]:
                    slot = "IJ"
                else:
                    slot = None
                if slot:
                    label_key = f"{day}_{slot}"
                    print(f"課程: {txt} 放在 {label_key}")   # debug
                    label = self.display_labels.get(label_key)
                    if label:
                        prev = label.text()
                        label.setText(prev + '\n' + txt if prev else txt)

    def grab_screenshot(self):
        pixmap = self.grab()
        pixmap.save("class.jpg", "JPG")

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())