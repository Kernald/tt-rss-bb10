#ifndef __MODEL_FILTER_HPP__
#define __MODEL_FILTER_HPP__

#include <bb/cascades/DataModel>
#include <QtCore/QHash>

namespace ttrss {
	class ModelFilter: public bb::cascades::DataModel {

		Q_OBJECT

		Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged);

	public:
		ModelFilter(bb::cascades::DataModel *sourceModel, QObject *parent = 0);
		virtual ~ModelFilter();

	    int childCount(const QVariantList& proxyIndexPath) const;
	    virtual int childCount(const QVariantList& proxyIndexPath);
	    virtual bool hasChildren(const QVariantList& proxyIndexPath);
	    virtual QVariant data(const QVariantList& proxyIndexPath);
	    virtual QString itemType(const QVariantList& proxyIndexPath);

	    bool isEmpty() const;

	Q_SIGNALS:
		void emptyChanged(bool isEmpty);

	protected:
	    virtual bool isSourceIndexFiltered(const QVariantList& sourceIndexPath) const = 0;

	    void setFilterStatus(bool filtered);
	    bool getFilterStatus() const;
	    void refreshFilter();
	    bb::cascades::DataModel* getSourceDataModel() const;
	    QVariantList proxyToSource(const QVariantList& proxyIndexPath, bool& ok) const;
	    QVariantList sourceToProxy(const QVariantList& sourceIndexPath) const;

	private Q_SLOTS:
		void handleAdd(const QVariantList& sourceIndexPath);
		void handleUpdate(const QVariantList& sourceIndexPath);
		void handleRemove(const QVariantList& sourceIndexPath);

	private:
	    void fillMapping();
	    int childCount_impl(const QVariantList& proxyIndexPath) const;

	    bb::cascades::DataModel*			_sourceDataModel;
	    bool								_filtered;
	    QHash<QVariantList, QVariantList>	_filterMapping;
	};

	inline int ModelFilter::childCount(const QVariantList& proxyIndexPath) const {
		return childCount_impl(proxyIndexPath);
	}

	inline int ModelFilter::childCount(const QVariantList& proxyIndexPath) {
		return childCount_impl(proxyIndexPath);
	}

	inline bool ModelFilter::getFilterStatus() const {
		return _filtered;
	}

	inline bb::cascades::DataModel* ModelFilter::getSourceDataModel() const {
		return _sourceDataModel;
	}
}

// Warning: only working for int variants
inline uint qHash(const QVariantList& key) {
	uint res = 0;
	foreach (QVariant v, key) {
		res ^= qHash(v.toInt());
	}
	return res;
}

#endif // __MODEL_FILTER_HPP__
