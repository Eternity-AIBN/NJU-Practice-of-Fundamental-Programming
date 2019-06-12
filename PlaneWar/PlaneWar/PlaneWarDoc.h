
// PlaneWarDoc.h : CPlaneWarDoc ��Ľӿ�
//


#pragma once
#include"GameRun.h"

class CPlaneWarDoc : public CDocument
{
protected: // �������л�����
	CPlaneWarDoc();
	DECLARE_DYNCREATE(CPlaneWarDoc)

	// ����
public:

	// ����
public:
	const CImage& getBackground() const { return background; }
	int getHeight() { return gameRun.getHeight(); }
	int getWidth() { return gameRun.getWidth(); }
	void playerMove(int act) { gameRun.playerMove(act); }
	void launchBullet() { gameRun.launchBullet(); }  //�����ӵ�
	void updateBullets() { gameRun.updateBullets(); }
	void updateEnemies() { gameRun.updateEnemies(); }
	bool isGameOver() { return gameRun.gameOver(); }
	void init() { gameRun.init(); }
	const MyPlane &getPlanePlayer() const { return gameRun.getPlanePlayer(); }
	const vector<Enemy> &getEnemy() const { return gameRun.getEnemy(); }
	const vector<Bullet> &getBullet() const { return gameRun.getBullet(); }
	int getScore() const { return gameRun.getScore(); }

	// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// ʵ��
public:
	virtual ~CPlaneWarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GameRun gameRun;
	CImage background;

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
