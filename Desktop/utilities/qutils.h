//
// Copyright (C) 2013-2018 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.
//

#ifndef QUTILS_H
#define QUTILS_H

#include <QJSValueIterator>
#include <QStringList>
#include <QQuickItem>
#include <QProcess>
#include <QJSValue>
#include <QString>
#include <QVector>
#include <QMap>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include "jsonredirect.h"

enum Encryption { NoEncryption, SimpleCryptEncryption };

inline	std::string							fq (const QString							 & from)	{ return from.toUtf8().toStdString(); }
		std::vector<std::string>			fq (const QVector<QString>					 & vec);
inline	std::vector<std::string>			fq (const QStringList						 & vec)		{ return fq(vec.toVector()); }
		std::map<std::string, std::string>	fq (const QMap<QString, QString>			 & map);
		QMap<QString, QString>				tq (const std::map<std::string, std::string> & map);
inline	QString								tq (const std::string						 & from)	{ return QString::fromUtf8(from.c_str(), from.length()); }
		QVector<QString>					tq (const std::vector<std::string>			 & vec);
		QStringList							tql(const std::vector<std::string>			 & from);
inline	QStringList							tql(const std::set<std::string>				 & from)	{ return tql(std::vector<std::string>(from.begin(), from.end())); }

		//These need to have a different name because otherwise the default Json::Value(const std::string & str) constructor steals any fq(std::string()) call...
		Json::Value							fqj(const QJSValue							 & jsVal);
		QJSValue							tqj(const Json::Value						 & json,	const QQuickItem * qItem);

		std::vector<std::string>			fromQstringToStdVector(const QString &input, const QString &delimeter);

template<typename T> inline		std::vector<T>	fq(QVector<T>		in) { return in.toStdVector();				}
template<typename T> inline		QVector<T>		tq(std::vector<T>	in) { return QVector<T>::fromStdVector(in); }

QString stripFirstAndLastChar(QString in, const QString &strip);
QString getShortCutKey();
QString encrypt(const QString &input);
QString decrypt(const QString &input);
QString getSortableTimestamp();
QString QJSErrorToString(QJSValue::ErrorType errorType);

QString shortenWinPaths(QString);

bool pathIsSafeForR(const QString & checkThis);

const char * QProcessErrorToString(QProcess::ProcessError error);

inline std::ostream& operator<<(std::ostream& os, const QString & qStr) { return (os << qStr.toStdString()); }

#define GENERIC_SET_FUNCTION(WHAT_TO_SET, VARIABLE_TO_SET, EMIT_THIS, TYPE)	\
void set##WHAT_TO_SET(TYPE new##WHAT_TO_SET)								\
{																			\
	if(new##WHAT_TO_SET != VARIABLE_TO_SET)									\
	{																		\
		VARIABLE_TO_SET = new##WHAT_TO_SET;									\
		emit EMIT_THIS();													\
	}																		\
}



#endif // QUTILS_H
