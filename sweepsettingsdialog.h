#ifndef SWEEPSETTINGSDIALOG_H
#define SWEEPSETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QStringList>
#include <QHash>
#include <QVector>
#include <QPair>

// 扫荡关卡配置结构
struct SweepStageConfig {
    int taskIndex;      // 任务索引
    int subTaskIndex;   // 子任务索引
};

// 窗口的困难扫荡配置
struct WindowSweepConfig {
    bool enabled;                          // 是否启用困难扫荡
    QVector<SweepStageConfig> stages;     // 扫荡关卡列表
};

class SweepSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SweepSettingsDialog(QWidget *parent = nullptr);
    ~SweepSettingsDialog();
    
    // 设置窗口标题列表并重建界面
    void setWindowTitles(const QStringList &titles);
    
    // 获取指定窗口的困难扫荡配置
    WindowSweepConfig getSweepConfig(const QString &windowTitle) const;
    
    // 设置指定窗口的困难扫荡配置
    void setSweepConfig(const QString &windowTitle, const WindowSweepConfig &config);
    
    // 获取所有窗口的困难扫荡配置
    QHash<QString, WindowSweepConfig> getAllSweepConfigs() const;
    
    // 设置所有窗口的困难扫荡配置
    void setAllSweepConfigs(const QHash<QString, WindowSweepConfig> &configs);

private slots:
    void onAddStageButtonClicked();
    void onRemoveStageButtonClicked();
    void onSaveButtonClicked();
    void onHelpButtonClicked();  // 使用说明按钮

private:
    void setupUi();
    QListWidget* getCurrentStageList();
    QCheckBox* getCurrentEnabledCheckBox();
    
    // UI控件
    QTabWidget *tabWidget;
    
    // 每个标签页的控件
    struct TabWidgets {
        QCheckBox *enabledCheckBox;         // 是否启用困难扫荡
        QListWidget *stageList;              // 扫荡关卡列表
        QPushButton *addStageButton;
        QPushButton *removeStageButton;
        QSpinBox *taskIndexSpinBox;          // 任务索引输入
        QSpinBox *subTaskIndexSpinBox;       // 子任务索引输入
    };
    
    QHash<QString, TabWidgets> tabWidgetsMap;
    
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QPushButton *helpButton;  // 使用说明按钮
    
    // 窗口标题列表
    QStringList windowTitles;
    
    // 创建单个标签页
    QWidget* createTabPage(const QString &windowTitle);
};

#endif // SWEEPSETTINGSDIALOG_H
