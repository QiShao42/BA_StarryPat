#include "studentinvitedialog.h"
#include <QDir>
#include <QFileInfo>
#include <QScrollArea>
#include <QTableWidget>
#include <QHeaderView>
#include <QCoreApplication>
#include <QSet>

StudentInviteDialog::StudentInviteDialog(QWidget *parent)
    : QDialog(parent)
{
    // 初始化时窗口标题列表为空，等待外部设置
    
    // 加载可用学生列表
    loadAvailableStudents();
    
    setupUi();
}

StudentInviteDialog::~StudentInviteDialog()
{
}

void StudentInviteDialog::loadAvailableStudents()
{
    // 从外部文件夹和内置资源加载学生名字
    availableStudents.clear();
    
    // 使用 QSet 去重
    QSet<QString> studentSet;
    
    // 第一步：从外部文件夹加载
    QString externalPath = QCoreApplication::applicationDirPath() + "/templates/student_avatar";
    QDir externalDir(externalPath);
    if (externalDir.exists()) {
        QStringList filters;
        filters << "*.png" << "*.PNG";
        QFileInfoList externalFiles = externalDir.entryInfoList(filters, QDir::Files);
        
        for (const QFileInfo &fileInfo : externalFiles) {
            // 文件名（不含扩展名）就是学生名字
            studentSet.insert(fileInfo.baseName());
        }
    }
    
    // 第二步：从内置资源加载
    QDir resourceDir(":/images/student_avatar");
    if (resourceDir.exists()) {
        QStringList filters;
        filters << "*.png";
        QFileInfoList resourceFiles = resourceDir.entryInfoList(filters, QDir::Files);
        
        for (const QFileInfo &fileInfo : resourceFiles) {
            // 文件名（不含扩展名）就是学生名字
            studentSet.insert(fileInfo.baseName());
        }
    }
    
    // 转换为列表并排序
    availableStudents = QList<QString>(studentSet.begin(), studentSet.end());
    availableStudents.sort();
}

void StudentInviteDialog::refreshAvailableStudentsInTabs()
{
    // 遍历所有标签页，更新可用学生列表
    for (auto it = tabWidgetsMap.begin(); it != tabWidgetsMap.end(); ++it) {
        const QString &windowTitle = it.key();
        TabWidgets &widgets = it.value();
        
        // 保存当前选中的学生（如果有）
        QListWidgetItem *currentItem = widgets.availableList->currentItem();
        QString selectedStudent;
        if (currentItem) {
            selectedStudent = currentItem->text();
        }
        
        // 保存当前搜索文本
        QString searchText = widgets.searchBox->text();
        
        // 清空并重新填充可用学生列表
        widgets.availableList->clear();
        for (const QString &student : availableStudents) {
            widgets.availableList->addItem(student);
        }
        
        // 重新应用搜索过滤
        if (!searchText.isEmpty()) {
            for (int i = 0; i < widgets.availableList->count(); i++) {
                QListWidgetItem *item = widgets.availableList->item(i);
                if (item) {
                    bool matches = item->text().contains(searchText, Qt::CaseInsensitive);
                    item->setHidden(!matches);
                }
            }
        }
        
        // 恢复选中状态（如果该学生仍然存在）
        if (!selectedStudent.isEmpty()) {
            QList<QListWidgetItem*> items = widgets.availableList->findItems(selectedStudent, Qt::MatchExactly);
            if (!items.isEmpty()) {
                widgets.availableList->setCurrentItem(items.first());
            }
        }
    }
}

void StudentInviteDialog::setupUi()
{
    this->setWindowTitle("邀请学生设置");
    this->setFixedSize(650, 580);
    this->setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    
    // 说明标签
    QLabel *infoLabel = new QLabel("为每个窗口设置要邀请的学生列表（按优先级排序）", this);
    infoLabel->setStyleSheet("font-size: 10pt; color: #666;");
    mainLayout->addWidget(infoLabel);
    
    // 创建标签页控件
    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet("QTabWidget::pane { "
                            "border: 2px solid #FF9800; "
                            "border-radius: 5px; "
                            "} "
                            "QTabBar::tab { "
                            "background-color: rgba(255, 152, 0, 100); "
                            "color: #333; "
                            "padding: 8px 20px; "
                            "margin-right: 2px; "
                            "border-top-left-radius: 5px; "
                            "border-top-right-radius: 5px; "
                            "} "
                            "QTabBar::tab:selected { "
                            "background-color: #FF9800; "
                            "color: white; "
                            "font-weight: bold; "
                            "}");
    
    // 为每个窗口标题创建标签页
    for (const QString &title : windowTitles) {
        QWidget *tabPage = createTabPage(title);
        tabWidget->addTab(tabPage, title);
    }
    
    mainLayout->addWidget(tabWidget);
    
    // 底部按钮行
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    
    saveButton = new QPushButton("保存", this);
    saveButton->setMinimumHeight(35);
    saveButton->setStyleSheet("QPushButton { "
                             "background-color: rgba(76, 175, 80, 200); "
                             "color: white; "
                             "border: 2px solid rgba(76, 175, 80, 255); "
                             "border-radius: 5px; "
                             "font-weight: bold; "
                             "padding: 5px 20px; "
                             "} "
                             "QPushButton:hover { "
                             "background-color: #4CAF50; "
                             "} "
                             "QPushButton:pressed { "
                             "background-color: #388E3C; "
                             "}");
    connect(saveButton, &QPushButton::clicked, this, &StudentInviteDialog::onSaveButtonClicked);
    buttonLayout->addWidget(saveButton);
    
    cancelButton = new QPushButton("取消", this);
    cancelButton->setMinimumHeight(35);
    cancelButton->setStyleSheet("QPushButton { "
                               "background-color: rgba(158, 158, 158, 200); "
                               "color: white; "
                               "border: 2px solid rgba(158, 158, 158, 255); "
                               "border-radius: 5px; "
                               "font-weight: bold; "
                               "padding: 5px 20px; "
                               "} "
                               "QPushButton:hover { "
                               "background-color: #9E9E9E; "
                               "} "
                               "QPushButton:pressed { "
                               "background-color: #757575; "
                               "}");
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
}

QWidget* StudentInviteDialog::createTabPage(const QString &windowTitle)
{
    QWidget *page = new QWidget();
    QVBoxLayout *mainPageLayout = new QVBoxLayout(page);
    mainPageLayout->setSpacing(10);
    mainPageLayout->setContentsMargins(10, 10, 10, 10);
    
    // 上半部分：邀请学生设置（水平布局）
    QWidget *studentWidget = new QWidget(page);
    QHBoxLayout *pageLayout = new QHBoxLayout(studentWidget);
    pageLayout->setSpacing(10);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    
    TabWidgets widgets;
    
    // 左侧：可选学生列表
    QGroupBox *availableGroup = new QGroupBox("可选学生", page);
    availableGroup->setStyleSheet("QGroupBox { "
                                 "border: 1px solid #ccc; "
                                 "border-radius: 5px; "
                                 "margin-top: 10px; "
                                 "font-weight: bold; "
                                 "} "
                                 "QGroupBox::title { "
                                 "subcontrol-origin: margin; "
                                 "subcontrol-position: top center; "
                                 "padding: 0 5px; "
                                 "}");
    QVBoxLayout *availableLayout = new QVBoxLayout(availableGroup);
    
    // 添加搜索框
    widgets.searchBox = new QLineEdit(availableGroup);
    widgets.searchBox->setPlaceholderText("搜索学生名称...");
    widgets.searchBox->setClearButtonEnabled(true);  // 添加清除按钮
    widgets.searchBox->setStyleSheet("QLineEdit { "
                                    "border: 1px solid #ddd; "
                                    "border-radius: 3px; "
                                    "padding: 5px; "
                                    "background-color: white; "
                                    "} "
                                    "QLineEdit:focus { "
                                    "border: 1px solid #FF9800; "
                                    "}");
    connect(widgets.searchBox, &QLineEdit::textChanged, 
            this, &StudentInviteDialog::onSearchTextChanged);
    availableLayout->addWidget(widgets.searchBox);
    
    widgets.availableList = new QListWidget(availableGroup);
    widgets.availableList->setStyleSheet("QListWidget { "
                                        "border: 1px solid #ddd; "
                                        "border-radius: 3px; "
                                        "} "
                                        "QListWidget::item { "
                                        "padding: 5px; "
                                        "} "
                                        "QListWidget::item:selected { "
                                        "background-color: #FF9800; "
                                        "color: white; "
                                        "}");
    // 添加所有可用学生
    for (const QString &student : availableStudents) {
        widgets.availableList->addItem(student);
    }
    connect(widgets.availableList, &QListWidget::itemDoubleClicked, 
            this, &StudentInviteDialog::onAvailableListDoubleClicked);
    availableLayout->addWidget(widgets.availableList);
    
    pageLayout->addWidget(availableGroup);
    
    // 中间：操作按钮
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setSpacing(5);
    buttonLayout->addStretch();
    
    widgets.addButton = new QPushButton("添加 >>", page);
    widgets.addButton->setMinimumHeight(30);
    widgets.addButton->setStyleSheet("QPushButton { "
                                    "background-color: rgba(255, 152, 0, 150); "
                                    "color: white; "
                                    "border: 1px solid #FF9800; "
                                    "border-radius: 3px; "
                                    "padding: 5px 10px; "
                                    "} "
                                    "QPushButton:hover { "
                                    "background-color: #FF9800; "
                                    "}");
    connect(widgets.addButton, &QPushButton::clicked, this, &StudentInviteDialog::onAddButtonClicked);
    buttonLayout->addWidget(widgets.addButton);
    
    widgets.removeButton = new QPushButton("<< 移除", page);
    widgets.removeButton->setMinimumHeight(30);
    widgets.removeButton->setStyleSheet("QPushButton { "
                                       "background-color: rgba(244, 67, 54, 150); "
                                       "color: white; "
                                       "border: 1px solid #F44336; "
                                       "border-radius: 3px; "
                                       "padding: 5px 10px; "
                                       "} "
                                       "QPushButton:hover { "
                                       "background-color: #F44336; "
                                       "}");
    connect(widgets.removeButton, &QPushButton::clicked, this, &StudentInviteDialog::onRemoveButtonClicked);
    buttonLayout->addWidget(widgets.removeButton);
    
    buttonLayout->addSpacing(20);
    
    widgets.moveUpButton = new QPushButton("上移 ↑", page);
    widgets.moveUpButton->setMinimumHeight(30);
    widgets.moveUpButton->setStyleSheet("QPushButton { "
                                       "background-color: rgba(33, 150, 243, 150); "
                                       "color: white; "
                                       "border: 1px solid #2196F3; "
                                       "border-radius: 3px; "
                                       "padding: 5px 10px; "
                                       "} "
                                       "QPushButton:hover { "
                                       "background-color: #2196F3; "
                                       "}");
    connect(widgets.moveUpButton, &QPushButton::clicked, this, &StudentInviteDialog::onMoveUpButtonClicked);
    buttonLayout->addWidget(widgets.moveUpButton);
    
    widgets.moveDownButton = new QPushButton("下移 ↓", page);
    widgets.moveDownButton->setMinimumHeight(30);
    widgets.moveDownButton->setStyleSheet("QPushButton { "
                                         "background-color: rgba(33, 150, 243, 150); "
                                         "color: white; "
                                         "border: 1px solid #2196F3; "
                                         "border-radius: 3px; "
                                         "padding: 5px 10px; "
                                         "} "
                                         "QPushButton:hover { "
                                         "background-color: #2196F3; "
                                         "}");
    connect(widgets.moveDownButton, &QPushButton::clicked, this, &StudentInviteDialog::onMoveDownButtonClicked);
    buttonLayout->addWidget(widgets.moveDownButton);
    
    buttonLayout->addStretch();
    pageLayout->addLayout(buttonLayout);
    
    // 右侧：已选学生表格（包含强制换装选项）
    QGroupBox *selectedGroup = new QGroupBox("已选学生（按优先级）", page);
    selectedGroup->setStyleSheet("QGroupBox { "
                                "border: 1px solid #ccc; "
                                "border-radius: 5px; "
                                "margin-top: 10px; "
                                "font-weight: bold; "
                                "} "
                                "QGroupBox::title { "
                                "subcontrol-origin: margin; "
                                "subcontrol-position: top center; "
                                "padding: 0 5px; "
                                "}");
    QVBoxLayout *selectedLayout = new QVBoxLayout(selectedGroup);
    
    // 创建表格（2列：学生名称、强制换装）
    widgets.selectedTable = new QTableWidget(0, 2, selectedGroup);
    widgets.selectedTable->setHorizontalHeaderLabels(QStringList() << "学生名称" << "强制换装");
    widgets.selectedTable->verticalHeader()->setVisible(true);
    widgets.selectedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    widgets.selectedTable->setSelectionMode(QAbstractItemView::SingleSelection);
    widgets.selectedTable->setStyleSheet("QTableWidget { "
                                        "border: 1px solid #ddd; "
                                        "border-radius: 3px; "
                                        "gridline-color: #ddd; "
                                        "background-color: white; "
                                        "} "
                                        "QHeaderView::section { "
                                        "background-color: rgba(102, 204, 255, 150); "
                                        "color: white; "
                                        "font-weight: bold; "
                                        "padding: 5px; "
                                        "border: none; "
                                        "} "
                                        "QTableWidget::item { "
                                        "padding: 5px; "
                                        "} "
                                        "QTableWidget::item:selected { "
                                        "background-color: #FF9800; "
                                        "color: white; "
                                        "}");
    
    // 设置列宽
    widgets.selectedTable->setColumnWidth(0, 130);  // 学生名称列
    widgets.selectedTable->setColumnWidth(1, 70);   // 强制换装列
    
    // 设置表头样式
    widgets.selectedTable->horizontalHeader()->setStyleSheet("QHeaderView::section { "
                                                             "background-color: #66CCFF; "
                                                             "color: white; "
                                                             "font-weight: bold; "
                                                             "padding: 8px; "
                                                             "border: none; "
                                                             "}");
    
    // 双击表格项时移除学生（保持原有功能）
    connect(widgets.selectedTable, &QTableWidget::itemDoubleClicked,
            this, &StudentInviteDialog::onSelectedTableDoubleClicked);
    
    selectedLayout->addWidget(widgets.selectedTable);
    pageLayout->addWidget(selectedGroup);
    
    mainPageLayout->addWidget(studentWidget);
    
    // 保存控件引用
    tabWidgetsMap[windowTitle] = widgets;
    
    return page;
}

QListWidget* StudentInviteDialog::getCurrentAvailableList()
{
    int index = tabWidget->currentIndex();
    if (index >= 0 && index < windowTitles.size()) {
        return tabWidgetsMap[windowTitles[index]].availableList;
    }
    return nullptr;
}

QTableWidget* StudentInviteDialog::getCurrentSelectedTable()
{
    int index = tabWidget->currentIndex();
    if (index >= 0 && index < windowTitles.size()) {
        return tabWidgetsMap[windowTitles[index]].selectedTable;
    }
    return nullptr;
}

void StudentInviteDialog::onAddButtonClicked()
{
    QListWidget *availableList = getCurrentAvailableList();
    QTableWidget *selectedTable = getCurrentSelectedTable();
    
    if (!availableList || !selectedTable) return;
    
    QListWidgetItem *item = availableList->currentItem();
    if (item) {
        QString studentName = item->text();
        
        // 检查是否已经添加
        bool exists = false;
        for (int i = 0; i < selectedTable->rowCount(); i++) {
            QTableWidgetItem *nameItem = selectedTable->item(i, 0);
            if (nameItem && nameItem->text() == studentName) {
                exists = true;
                break;
            }
        }
        
        if (!exists) {
            // 添加新行
            int row = selectedTable->rowCount();
            selectedTable->insertRow(row);
            
            // 第1列：学生名称
            QTableWidgetItem *nameItem = new QTableWidgetItem(studentName);
            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);  // 不可编辑
            selectedTable->setItem(row, 0, nameItem);
            
            // 第2列：强制换装复选框（居中显示）
            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layout = new QHBoxLayout(checkBoxWidget);
            layout->addWidget(checkBox);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            checkBoxWidget->setLayout(layout);
            selectedTable->setCellWidget(row, 1, checkBoxWidget);
        }
    }
}

void StudentInviteDialog::onRemoveButtonClicked()
{
    QTableWidget *selectedTable = getCurrentSelectedTable();
    if (!selectedTable) return;
    
    int currentRow = selectedTable->currentRow();
    if (currentRow >= 0) {
        selectedTable->removeRow(currentRow);
    }
}

void StudentInviteDialog::onMoveUpButtonClicked()
{
    QTableWidget *selectedTable = getCurrentSelectedTable();
    if (!selectedTable) return;
    
    int currentRow = selectedTable->currentRow();
    if (currentRow > 0) {
        // 保存当前行的数据
        QString studentName = selectedTable->item(currentRow, 0)->text();
        QWidget *checkBoxWidget = selectedTable->cellWidget(currentRow, 1);
        QCheckBox *checkBox = checkBoxWidget ? checkBoxWidget->findChild<QCheckBox*>() : nullptr;
        bool isForceInvite = checkBox ? checkBox->isChecked() : false;
        
        // 移除当前行
        selectedTable->removeRow(currentRow);
        
        // 在上一行位置插入
        selectedTable->insertRow(currentRow - 1);
        
        // 恢复数据 - 第1列：学生名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(studentName);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        selectedTable->setItem(currentRow - 1, 0, nameItem);
        
        // 恢复数据 - 第2列：强制换装复选框
        QWidget *newCheckBoxWidget = new QWidget();
        QCheckBox *newCheckBox = new QCheckBox();
        newCheckBox->setChecked(isForceInvite);
        QHBoxLayout *layout = new QHBoxLayout(newCheckBoxWidget);
        layout->addWidget(newCheckBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        newCheckBoxWidget->setLayout(layout);
        selectedTable->setCellWidget(currentRow - 1, 1, newCheckBoxWidget);
        
        // 设置当前行
        selectedTable->setCurrentCell(currentRow - 1, 0);
    }
}

void StudentInviteDialog::onMoveDownButtonClicked()
{
    QTableWidget *selectedTable = getCurrentSelectedTable();
    if (!selectedTable) return;
    
    int currentRow = selectedTable->currentRow();
    if (currentRow >= 0 && currentRow < selectedTable->rowCount() - 1) {
        // 保存当前行的数据
        QString studentName = selectedTable->item(currentRow, 0)->text();
        QWidget *checkBoxWidget = selectedTable->cellWidget(currentRow, 1);
        QCheckBox *checkBox = checkBoxWidget ? checkBoxWidget->findChild<QCheckBox*>() : nullptr;
        bool isForceInvite = checkBox ? checkBox->isChecked() : false;
        
        // 移除当前行
        selectedTable->removeRow(currentRow);
        
        // 在下一行位置插入
        selectedTable->insertRow(currentRow + 1);
        
        // 恢复数据 - 第1列：学生名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(studentName);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        selectedTable->setItem(currentRow + 1, 0, nameItem);
        
        // 恢复数据 - 第2列：强制换装复选框
        QWidget *newCheckBoxWidget = new QWidget();
        QCheckBox *newCheckBox = new QCheckBox();
        newCheckBox->setChecked(isForceInvite);
        QHBoxLayout *layout = new QHBoxLayout(newCheckBoxWidget);
        layout->addWidget(newCheckBox);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        newCheckBoxWidget->setLayout(layout);
        selectedTable->setCellWidget(currentRow + 1, 1, newCheckBoxWidget);
        
        // 设置当前行
        selectedTable->setCurrentCell(currentRow + 1, 0);
    }
}

void StudentInviteDialog::onSaveButtonClicked()
{
    this->accept();
}

void StudentInviteDialog::onAvailableListDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    onAddButtonClicked();
}

void StudentInviteDialog::onSelectedTableDoubleClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
    onRemoveButtonClicked();
}

QStringList StudentInviteDialog::getStudentList(const QString &windowTitle) const
{
    QStringList students;
    if (tabWidgetsMap.contains(windowTitle)) {
        QTableWidget *selectedTable = tabWidgetsMap[windowTitle].selectedTable;
        for (int i = 0; i < selectedTable->rowCount(); i++) {
            QTableWidgetItem *item = selectedTable->item(i, 0);
            if (item) {
                students.append(item->text());
            }
        }
    }
    return students;
}

void StudentInviteDialog::setStudentList(const QString &windowTitle, const QStringList &students)
{
    if (tabWidgetsMap.contains(windowTitle)) {
        QTableWidget *selectedTable = tabWidgetsMap[windowTitle].selectedTable;
        selectedTable->setRowCount(0);  // 清空表格
        
        for (const QString &student : students) {
            int row = selectedTable->rowCount();
            selectedTable->insertRow(row);
            
            // 第1列：学生名称
            QTableWidgetItem *nameItem = new QTableWidgetItem(student);
            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
            selectedTable->setItem(row, 0, nameItem);
            
            // 第2列：强制换装复选框（默认不勾选）
            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layout = new QHBoxLayout(checkBoxWidget);
            layout->addWidget(checkBox);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            checkBoxWidget->setLayout(layout);
            selectedTable->setCellWidget(row, 1, checkBoxWidget);
        }
    }
}

QHash<QString, QStringList> StudentInviteDialog::getAllStudentLists() const
{
    QHash<QString, QStringList> lists;
    for (const QString &title : windowTitles) {
        lists[title] = getStudentList(title);
    }
    return lists;
}

void StudentInviteDialog::setAllStudentLists(const QHash<QString, QStringList> &lists)
{
    for (auto it = lists.constBegin(); it != lists.constEnd(); ++it) {
        setStudentList(it.key(), it.value());
    }
}

QHash<QString, bool> StudentInviteDialog::getForceInviteSettings(const QString &windowTitle) const
{
    QHash<QString, bool> settings;
    if (tabWidgetsMap.contains(windowTitle)) {
        QTableWidget *selectedTable = tabWidgetsMap[windowTitle].selectedTable;
        for (int i = 0; i < selectedTable->rowCount(); i++) {
            QTableWidgetItem *nameItem = selectedTable->item(i, 0);
            if (nameItem) {
                QString studentName = nameItem->text();
                QWidget *checkBoxWidget = selectedTable->cellWidget(i, 1);
                QCheckBox *checkBox = checkBoxWidget ? checkBoxWidget->findChild<QCheckBox*>() : nullptr;
                if (checkBox) {
                    settings[studentName] = checkBox->isChecked();
                }
            }
        }
    }
    return settings;
}

void StudentInviteDialog::setForceInviteSettings(const QString &windowTitle, const QHash<QString, bool> &settings)
{
    if (tabWidgetsMap.contains(windowTitle)) {
        QTableWidget *selectedTable = tabWidgetsMap[windowTitle].selectedTable;
        for (int i = 0; i < selectedTable->rowCount(); i++) {
            QTableWidgetItem *nameItem = selectedTable->item(i, 0);
            if (nameItem) {
                QString studentName = nameItem->text();
                if (settings.contains(studentName)) {
                    QWidget *checkBoxWidget = selectedTable->cellWidget(i, 1);
                    QCheckBox *checkBox = checkBoxWidget ? checkBoxWidget->findChild<QCheckBox*>() : nullptr;
                    if (checkBox) {
                        checkBox->setChecked(settings[studentName]);
                    }
                }
            }
        }
    }
}

QHash<QString, bool> StudentInviteDialog::getAllForceInviteSettings() const
{
    QHash<QString, bool> allSettings;
    for (const QString &title : windowTitles) {
        QHash<QString, bool> settings = getForceInviteSettings(title);
        // 使用 "窗口标题|学生名称" 作为key
        for (auto it = settings.constBegin(); it != settings.constEnd(); ++it) {
            QString key = title + "|" + it.key();
            allSettings[key] = it.value();
        }
    }
    return allSettings;
}

void StudentInviteDialog::setAllForceInviteSettings(const QHash<QString, bool> &settings)
{
    // settings 的 key 格式是 "窗口标题|学生名称"
    QHash<QString, QHash<QString, bool>> settingsByWindow;
    
    // 按窗口分组
    for (auto it = settings.constBegin(); it != settings.constEnd(); ++it) {
        QString key = it.key();
        int separatorIndex = key.indexOf('|');
        if (separatorIndex > 0) {
            QString windowTitle = key.left(separatorIndex);
            QString studentName = key.mid(separatorIndex + 1);
            settingsByWindow[windowTitle][studentName] = it.value();
        }
    }
    
    // 应用设置
    for (auto it = settingsByWindow.constBegin(); it != settingsByWindow.constEnd(); ++it) {
        setForceInviteSettings(it.key(), it.value());
    }
}

void StudentInviteDialog::setWindowTitles(const QStringList &titles)
{
    // 如果标题列表没有变化，不需要重建
    if (titles == windowTitles) {
        return;
    }
    
    // 保存旧的设置
    QHash<QString, QStringList> oldStudentLists = getAllStudentLists();
    QHash<QString, bool> oldForceInvite = getAllForceInviteSettings();
    
    // 更新窗口标题列表
    windowTitles = titles;
    
    // 清空现有的标签页
    while (tabWidget->count() > 0) {
        QWidget *widget = tabWidget->widget(0);
        tabWidget->removeTab(0);
        delete widget;
    }
    tabWidgetsMap.clear();
    
    // 为新的窗口标题创建标签页
    for (const QString &title : windowTitles) {
        QWidget *tabPage = createTabPage(title);
        tabWidget->addTab(tabPage, title);
    }
    
    // // 恢复旧的设置（如果存在）
    // for (const QString &title : windowTitles) {
    //     if (oldStudentLists.contains(title)) {
    //         setStudentList(title, oldStudentLists[title]);
    //     }
    //     if (oldTaskParams.contains(title)) {
    //         setTaskParams(title, oldTaskParams[title].first, oldTaskParams[title].second);
    //     }
    //     if (oldSweepTask.contains(title)) {
    //         setSweepTaskEnabled(title, oldSweepTask[title]);
    //     }
    // }
    
    // 恢复强制邀请设置
    setAllForceInviteSettings(oldForceInvite);
}

void StudentInviteDialog::onSearchTextChanged(const QString &text)
{
    // 获取当前标签页的可用学生列表
    QListWidget *availableList = getCurrentAvailableList();
    if (!availableList) return;
    
    QString searchText = text.trimmed();
    
    // 遍历所有列表项
    for (int i = 0; i < availableList->count(); i++) {
        QListWidgetItem *item = availableList->item(i);
        if (item) {
            // 如果搜索文本为空，显示所有项
            // 否则只显示包含搜索文本的项（不区分大小写）
            if (searchText.isEmpty()) {
                item->setHidden(false);
            } else {
                bool matches = item->text().contains(searchText, Qt::CaseInsensitive);
                item->setHidden(!matches);
            }
        }
    }
}

