#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <QtCore/QObject>
#include <QtCore/QVariant>

class Settings : public QObject {

	Q_OBJECT

public:
	Settings();
	virtual ~Settings();

	Q_INVOKABLE QVariant getValueFor(const QString &objectName, const QVariant &defaultValue);
	Q_INVOKABLE void saveValueFor(const QString &objectName, const QVariant &inputValue);
};

#endif // __SETTINGS_HPP__
