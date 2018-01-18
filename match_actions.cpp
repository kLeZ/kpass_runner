#include "pass_runner.h"

using namespace std;

QList<Plasma::QueryMatch> KPassRunner::findPaths(QString &term)
{
	QList<Plasma::QueryMatch> matches;

	QDir root(m_path), current(m_path);
	if (term.contains(QDir::separator()))
	{
		current.cd(term);
	}

	Plasma::QueryMatch depth(this);
	depth.setType(Plasma::QueryMatch::Type::HelperMatch);
	depth.setText(term);
	depth.setSubtext(current.absolutePath());
	matches.append(depth);

	QStringList dirs = current.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable);
	QStringList files = current.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);

	foreach (QString dir, dirs)
	{
		if (dir.compare(term, Qt::CaseSensitivity::CaseInsensitive) == 0)
		{
			Plasma::QueryMatch match(this);
			match.setType(Plasma::QueryMatch::Type::InformationalMatch);
			match.setText(dir);
			match.setData(term.prepend(m_triggerWord).append('/'));
			matches.append(match);
		}
		else if (dir.startsWith(term, Qt::CaseSensitivity::CaseInsensitive))
		{
			Plasma::QueryMatch match(this);
			match.setType(Plasma::QueryMatch::Type::InformationalMatch);
			match.setText(dir);
			match.setData(dir.prepend(m_triggerWord).append('/'));
			matches.append(match);
		}
	}
	foreach (QString file, files)
	{
		Plasma::QueryMatch match(this);
		match.setType(Plasma::QueryMatch::Type::PossibleMatch);
		match.setText(file.remove(QLatin1String(".gpg"), Qt::CaseSensitivity::CaseInsensitive));
		match.setData(term.append(file));
		matches.append(match);
	}
	return matches;
}
