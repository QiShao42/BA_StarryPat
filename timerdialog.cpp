#include "timerdialog.h"
#include <QHeaderView>
#include <QTimeEdit>
#include <QCheckBox>
#include <QWidget>
#include <QHBoxLayout>

TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

TimerDialog::~TimerDialog()
{
}

void TimerDialog::setupUi()
{
    this->setWindowTitle("定时执行设置");
    this->setFixedSize(920, 480);
    this->setModal(true);
    
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    
    // 启用定时复选框
    enableTimerCheckBox = new QCheckBox("启用定时执行", this);
    enableTimerCheckBox->setStyleSheet("QCheckBox { "
                                      "font-weight: bold; "
                                      "font-size: 12pt; "
                                      "color: #FF9800; "
                                      "}");
    mainLayout->addWidget(enableTimerCheckBox);
    
    // 说明标签
    QLabel *infoLabel = new QLabel("配置定时任务（最多8个），每个任务可设置执行时间和操作项", this);
    infoLabel->setStyleSheet("font-size: 9pt; color: #666; padding: 5px 0;");
    mainLayout->addWidget(infoLabel);
    
    // 创建表格（调整为6列）
    taskTable = new QTableWidget(8, 6, this);
    taskTable->setHorizontalHeaderLabels(QStringList() << "启用该时段" << "定时时间" << "咖啡厅1邀请" << "咖啡厅2邀请" << "游戏静音" << "困难扫荡");
    taskTable->verticalHeader()->setVisible(true);
    taskTable->setStyleSheet("QTableWidget { "
                            "border: 2px solid #FF9800; "
                            "border-radius: 5px; "
                            "gridline-color: #ddd; "
                            "background-color: white; "
                            "} "
                            "QHeaderView::section { "
                            "background-color: rgba(255, 152, 0, 150); "
                            "color: white; "
                            "font-weight: bold; "
                            "padding: 5px; "
                            "border: none; "
                            "} "
                            "QTableWidget::item { "
                            "padding: 3px; "
                            "}");
    
    // 设置表头样式
    taskTable->horizontalHeader()->setStyleSheet("QHeaderView::section { "
                                                "background-color: #FF9800; "
                                                "color: white; "
                                                "font-weight: bold; "
                                                "padding: 8px; "
                                                "border: none; "
                                                "}");
    
    // 设置列宽
    taskTable->setColumnWidth(0, 100);  // 启用该时段列
    taskTable->setColumnWidth(1, 150);  // 时间列
    taskTable->setColumnWidth(2, 110);  // 咖啡厅1邀请列
    taskTable->setColumnWidth(3, 110);  // 咖啡厅2邀请列
    taskTable->setColumnWidth(4, 100);  // 静音列
    taskTable->setColumnWidth(5, 100);  // 困难扫荡列
    
    // 初始化表格内容
    for (int row = 0; row < 8; row++) {
        // 第1列：启用该时段复选框（居中显示）
        QWidget *enableWidget = new QWidget();
        QCheckBox *enableCheckBox = new QCheckBox();
        QHBoxLayout *enableLayout = new QHBoxLayout(enableWidget);
        enableLayout->addWidget(enableCheckBox);
        enableLayout->setAlignment(Qt::AlignCenter);
        enableLayout->setContentsMargins(0, 0, 0, 0);
        enableWidget->setLayout(enableLayout);
        taskTable->setCellWidget(row, 0, enableWidget);
        
        // 第2列：时间选择器
        QTimeEdit *timeEdit = new QTimeEdit();
        timeEdit->setDisplayFormat("HH:mm");
        timeEdit->setTime(QTime(0, 0));
        timeEdit->setStyleSheet("QTimeEdit { "
                               "border: 1px solid #ddd; "
                               "border-radius: 3px; "
                               "padding: 3px; "
                               "background-color: white; "
                               "}");
        taskTable->setCellWidget(row, 1, timeEdit);
        
        // 第3-6列:复选框(居中显示)
        for (int col = 2; col < 6; col++) {
            QWidget *widget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->addWidget(checkBox);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            widget->setLayout(layout);
            taskTable->setCellWidget(row, col, widget);
        }
    }
    
    mainLayout->addWidget(taskTable);
    
    // 清空按钮
    clearAllButton = new QPushButton("清空所有", this);
    clearAllButton->setMinimumHeight(30);
    clearAllButton->setStyleSheet("QPushButton { "
                                 "background-color: rgba(255, 152, 0, 150); "
                                 "color: white; "
                                 "border: 2px solid rgba(255, 152, 0, 255); "
                                 "border-radius: 5px; "
                                 "font-weight: bold; "
                                 "padding: 5px; "
                                 "} "
                                 "QPushButton:hover { "
                                 "background-color: rgba(255, 152, 0, 200); "
                                 "} "
                                 "QPushButton:pressed { "
                                 "background-color: rgba(245, 124, 0, 255); "
                                 "}");
    connect(clearAllButton, &QPushButton::clicked, this, &TimerDialog::onClearAllButtonClicked);
    mainLayout->addWidget(clearAllButton);
    
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
                             "padding: 5px; "
                             "} "
                             "QPushButton:hover { "
                             "background-color: #4CAF50; "
                             "} "
                             "QPushButton:pressed { "
                             "background-color: #388E3C; "
                             "}");
    connect(saveButton, &QPushButton::clicked, this, &TimerDialog::onSaveButtonClicked);
    buttonLayout->addWidget(saveButton);
    
    cancelButton = new QPushButton("取消", this);
    cancelButton->setMinimumHeight(35);
    cancelButton->setStyleSheet("QPushButton { "
                               "background-color: rgba(158, 158, 158, 200); "
                               "color: white; "
                               "border: 2px solid rgba(158, 158, 158, 255); "
                               "border-radius: 5px; "
                               "font-weight: bold; "
                               "padding: 5px; "
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

void TimerDialog::onClearAllButtonClicked()
{
    // 清空所有定时设置
    for (int row = 0; row < 8; row++) {
        // 取消所有复选框（包括第1列的启用复选框）
        for (int col = 0; col < 6; col++) {
            if (col == 1) continue;  // 跳过时间列
            
            QWidget *widget = taskTable->cellWidget(row, col);
            if (widget) {
                QCheckBox *checkBox = widget->findChild<QCheckBox*>();
                if (checkBox) {
                    checkBox->setChecked(false);
                }
            }
        }
        
        // 重置时间
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit*>(taskTable->cellWidget(row, 1));
        if (timeEdit) {
            timeEdit->setTime(QTime(0, 0));
        }
    }
}

void TimerDialog::onSaveButtonClicked()
{
    // 保存并关闭
    this->accept();
}

bool TimerDialog::isTimerEnabled() const
{
    return enableTimerCheckBox->isChecked();
}

QVector<TimerTaskConfig> TimerDialog::getTimerTasks() const
{
    QVector<TimerTaskConfig> tasks;
    
    for (int row = 0; row < 8; row++) {
        TimerTaskConfig config;
        
        // 获取启用状态
        QWidget *enableWidget = taskTable->cellWidget(row, 0);
        QCheckBox *enableCheckBox = enableWidget ? enableWidget->findChild<QCheckBox*>() : nullptr;
        config.enabled = enableCheckBox ? enableCheckBox->isChecked() : false;
        
        // 如果未启用，跳过
        if (!config.enabled) continue;
        
        // 获取时间
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit*>(taskTable->cellWidget(row, 1));
        if (!timeEdit) continue;
        config.time = timeEdit->time();
        
        // 获取咖啡厅1邀请开关
        QWidget *inviteCafe1Widget = taskTable->cellWidget(row, 2);
        QCheckBox *inviteCafe1CheckBox = inviteCafe1Widget ? inviteCafe1Widget->findChild<QCheckBox*>() : nullptr;
        config.inviteCafe1Enabled = inviteCafe1CheckBox ? inviteCafe1CheckBox->isChecked() : false;
        
        // 获取咖啡厅2邀请开关
        QWidget *inviteCafe2Widget = taskTable->cellWidget(row, 3);
        QCheckBox *inviteCafe2CheckBox = inviteCafe2Widget ? inviteCafe2Widget->findChild<QCheckBox*>() : nullptr;
        config.inviteCafe2Enabled = inviteCafe2CheckBox ? inviteCafe2CheckBox->isChecked() : false;
        
        // 获取静音开关
        QWidget *muteWidget = taskTable->cellWidget(row, 4);
        QCheckBox *muteCheckBox = muteWidget ? muteWidget->findChild<QCheckBox*>() : nullptr;
        config.muteEnabled = muteCheckBox ? muteCheckBox->isChecked() : false;
        
        // 获取困难扫荡开关
        QWidget *sweepWidget = taskTable->cellWidget(row, 5);
        QCheckBox *sweepCheckBox = sweepWidget ? sweepWidget->findChild<QCheckBox*>() : nullptr;
        config.sweepEnabled = sweepCheckBox ? sweepCheckBox->isChecked() : false;
        
        // 添加该任务
        tasks.append(config);
    }
    
    return tasks;
}

void TimerDialog::setTimerEnabled(bool enabled)
{
    enableTimerCheckBox->setChecked(enabled);
}

void TimerDialog::setTimerTasks(const QVector<TimerTaskConfig> &tasks)
{
    // 先清空所有设置
    onClearAllButtonClicked();
    
    // 设置新的任务配置
    int row = 0;
    for (const TimerTaskConfig &task : tasks) {
        if (row >= 8) break;
        
        // 设置启用状态
        QWidget *enableWidget = taskTable->cellWidget(row, 0);
        QCheckBox *enableCheckBox = enableWidget ? enableWidget->findChild<QCheckBox*>() : nullptr;
        if (enableCheckBox) {
            enableCheckBox->setChecked(task.enabled);
        }
        
        // 设置时间
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit*>(taskTable->cellWidget(row, 1));
        if (timeEdit) {
            timeEdit->setTime(task.time);
        }
        
        // 设置咖啡厅1邀请开关
        QWidget *inviteCafe1Widget = taskTable->cellWidget(row, 2);
        QCheckBox *inviteCafe1CheckBox = inviteCafe1Widget ? inviteCafe1Widget->findChild<QCheckBox*>() : nullptr;
        if (inviteCafe1CheckBox) {
            inviteCafe1CheckBox->setChecked(task.inviteCafe1Enabled);
        }
        
        // 设置咖啡厅2邀请开关
        QWidget *inviteCafe2Widget = taskTable->cellWidget(row, 3);
        QCheckBox *inviteCafe2CheckBox = inviteCafe2Widget ? inviteCafe2Widget->findChild<QCheckBox*>() : nullptr;
        if (inviteCafe2CheckBox) {
            inviteCafe2CheckBox->setChecked(task.inviteCafe2Enabled);
        }
        
        // 设置静音开关
        QWidget *muteWidget = taskTable->cellWidget(row, 4);
        QCheckBox *muteCheckBox = muteWidget ? muteWidget->findChild<QCheckBox*>() : nullptr;
        if (muteCheckBox) {
            muteCheckBox->setChecked(task.muteEnabled);
        }
        
        // 设置困难扫荡开关
        QWidget *sweepWidget = taskTable->cellWidget(row, 5);
        QCheckBox *sweepCheckBox = sweepWidget ? sweepWidget->findChild<QCheckBox*>() : nullptr;
        if (sweepCheckBox) {
            sweepCheckBox->setChecked(task.sweepEnabled);
        }
        
        row++;
    }
}
