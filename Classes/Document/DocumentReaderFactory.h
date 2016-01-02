#include <string>
#include <map>
#include <iterator>
#pragma once

/* Factory for creation of DocumentReader objects */
class DocumentReaderFactory
{
private:
	DocumentReaderFactory();
	DocumentReaderFactory(const DocumentReaderFactory &) { }
	DocumentReaderFactory &operator=(const DocumentReaderFactory &) { return *this; }

	typedef std::map<std::string, CreateDocumentReaderFn> FactoryMap;
	FactoryMap m_FactoryMap;
public:
	~DocumentReaderFactory() { m_FactoryMap.clear(); }

	static DocumentReaderFactory *Get()
	{
		static DocumentReaderFactory instance;
		return &instance;
	}

	void Register(const std::string &documentReaderName, CreateDocumentReaderFn pfnCreate);
	DocumentReader *CreateDocumentReader(const std::string &documentReaderName, const unsigned int version);
};

/*
Document Reader Factory constructor.
Register the types of DocumentReader here.
*/
DocumentReaderFactory::DocumentReaderFactory()
{
	Register("Node_1", &NodeDocumentReaderVersion_1::Create);
}

void DocumentReaderFactory::Register(const std::string &documentReaderName, CreateDocumentReaderFn pfnCreate)
{
	m_FactoryMap[documentReaderName] = pfnCreate;
}

DocumentReader *DocumentReaderFactory::CreateDocumentReader(const std::string &documentReaderName, const unsigned int version)
{
	FactoryMap::iterator it = m_FactoryMap.find(documentReaderName + "_" + boost::lexical_cast<std::string>(version));
	if (it != m_FactoryMap.end())
		return it->second();
	return NULL;
}