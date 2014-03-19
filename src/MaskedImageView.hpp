/*
 * MaskedImageView.h
 *
 *  Created on: Mar 19, 2014
 *      Author: rodrigopex
 */
#ifndef MASKEDIMAGEVIEW_H_
#define MASKEDIMAGEVIEW_H_

#include <bb/cascades/ImageView>
#include <bb/cascades/Container>
#include <bb/cascades/QmlDocument>


class MaskedImageView: public bb::cascades::ImageView {
	Q_OBJECT
	Q_PROPERTY(QUrl imageSource READ imageSource WRITE setMaskedImageSource NOTIFY imageSourceChanged)
public:
	MaskedImageView(bb::cascades::Container *parent = 0);
	virtual ~MaskedImageView();
	static void registerQmlTypes() {
		qmlRegisterType<MaskedImageView>("maskedImageView", 1, 0, "MaskedImageView");
	}
	Q_INVOKABLE QUrl imageSource() const;
	Q_INVOKABLE void setMaskedImageSource(const QUrl &source);
	Q_SIGNAL void imageSourceChanged(const QUrl &source);
private:
	QUrl m_imageSource;

};

#endif /* MASKEDIMAGEVIEW_H_ */
