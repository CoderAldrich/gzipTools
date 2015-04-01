
// gzipToolsDlg.h : ͷ�ļ�
//

#pragma once


// CgzipToolsDlg �Ի���
class CgzipToolsDlg : public CDialog
{
// ����
public:
	CgzipToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GZIPTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
        // Դ�ļ�·��
        CString m_strSrcPath;
        // Ŀ���ļ�·��
        CString m_strDstPath;
        CStatusBarCtrl m_StatusBar; // ״̬��
protected:
        virtual void OnCancel();
        virtual void OnOK();
public:
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        afx_msg void OnBnClickedSrcbrow();
        afx_msg void OnBnClickedDstbrow();
        afx_msg void OnBnClickedCompress();
        afx_msg void OnBnClickedUncompress();
        int gzipStream(bool bMode);
};
