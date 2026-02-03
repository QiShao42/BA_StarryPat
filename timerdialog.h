#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QTime>
#include <QVector>
#include <QTableWidget>

// 定时任务配置结构
struct TimerTaskConfig {
    QTime time;              // 定时时间
    bool inviteCafe1Enabled; // 是否在咖啡厅1邀请学生
    bool inviteCafe2Enabled; // 是否在咖啡厅2邀请学生
    bool muteEnabled;        // 是否静音
    bool sweepEnabled;       // 是否执行困难扫荡
    bool enabled;            // 该任务是否启用
};

class TimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimerDialog(QWidget *parent = nullptr);
    ~TimerDialog();
    
    // 获取定时设置
    bool isTimerEnabled() const;
    QVector<TimerTaskConfig> getTimerTasks() const;
    
    // 设置定时配置
    void setTimerEnabled(bool enabled);
    void setTimerTasks(const QVector<TimerTaskConfig> &tasks);

private slots:
    void onClearAllButtonClicked();
    void onSaveButtonClicked();

private:
    void setupUi();
    
    // UI控件
    QCheckBox *enableTimerCheckBox;
    QTableWidget *taskTable;
    QPushButton *clearAllButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    
    QVBoxLayout *mainLayout;
};

#endif // TIMERDIALOG_H

