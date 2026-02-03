#ifndef STUDENTINVITEDIALOG_H
#define STUDENTINVITEDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QStringList>
#include <QHash>
#include <QPair>

// 前置声明
class QTableWidgetItem;
class QListWidgetItem;

class StudentInviteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInviteDialog(QWidget *parent = nullptr);
    ~StudentInviteDialog();
    
    // 设置窗口标题列表并重建界面
    void setWindowTitles(const QStringList &titles);
    
    // 获取指定窗口的邀请学生列表
    QStringList getStudentList(const QString &windowTitle) const;
    
    // 设置指定窗口的邀请学生列表
    void setStudentList(const QString &windowTitle, const QStringList &students);
    
    // 获取所有窗口的学生列表
    QHash<QString, QStringList> getAllStudentLists() const;
    
    // 设置所有窗口的学生列表
    void setAllStudentLists(const QHash<QString, QStringList> &lists);
    
    // 获取指定窗口的强制邀请设置（按学生）
    QHash<QString, bool> getForceInviteSettings(const QString &windowTitle) const;
    
    // 设置指定窗口的强制邀请状态（按学生）
    void setForceInviteSettings(const QString &windowTitle, const QHash<QString, bool> &settings);
    
    // 获取所有窗口的强制邀请设置（按学生）
    // 返回格式: Key = "窗口标题|学生名称", Value = 是否强制邀请
    QHash<QString, bool> getAllForceInviteSettings() const;
    
    // 设置所有窗口的强制邀请状态（按学生）
    void setAllForceInviteSettings(const QHash<QString, bool> &settings);
    
    // 重新加载可用学生列表
    void loadAvailableStudents();
    
    // 刷新所有标签页的可用学生列表（在重新加载模板后调用）
    void refreshAvailableStudentsInTabs();

private slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onMoveUpButtonClicked();
    void onMoveDownButtonClicked();
    void onSaveButtonClicked();
    void onAvailableListDoubleClicked(QListWidgetItem *item);
    void onSelectedTableDoubleClicked(QTableWidgetItem *item);
    void onSearchTextChanged(const QString &text);

private:
    void setupUi();
    QListWidget* getCurrentAvailableList();
    QTableWidget* getCurrentSelectedTable();
    
    // UI控件
    QTabWidget *tabWidget;
    
    // 每个标签页的控件
    struct TabWidgets {
        QLineEdit *searchBox;        // 搜索框
        QListWidget *availableList;  // 可选学生列表
        QTableWidget *selectedTable; // 已选学生表格（包含学生名称和强制换装选项）
        QPushButton *addButton;
        QPushButton *removeButton;
        QPushButton *moveUpButton;
        QPushButton *moveDownButton;
    };
    
    QHash<QString, TabWidgets> tabWidgetsMap;
    
    QPushButton *saveButton;
    QPushButton *cancelButton;
    
    // 窗口标题列表
    QStringList windowTitles;
    
    // 可用学生名称列表
    QStringList availableStudents;
    
    // 创建单个标签页
    QWidget* createTabPage(const QString &windowTitle);
};

#endif // STUDENTINVITEDIALOG_H

