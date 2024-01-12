#include "stdio.h"

void cleanup(xmlSchemaValidCtxtPtr valid_ctxt, xmlSchemaPtr schema, xmlSchemaParserCtxtPtr parser_ctxt, xmlDocPtr doc) {
    // Освобождение ресурсов
    if (valid_ctxt != NULL) {
        xmlSchemaFreeValidCtxt(valid_ctxt);
    }

    if (schema != NULL) {
        xmlSchemaFree(schema);
    }

    if (parser_ctxt != NULL) {
        xmlSchemaFreeParserCtxt(parser_ctxt);
    }

    if (doc != NULL) {
        xmlFreeDoc(doc);
    }

    // Освобождение библиотеки libxml2
    xmlCleanupParser();
}


int validate_request_xml(xmlDocPtr xml_file, const char *xsd_filename) {
    // Инициализация библиотеки libxml2
    xmlInitParser();

    if (xml_file == NULL) {
        fprintf(stderr, "Failed to parse XML file.\n");
        xmlCleanupParser();
        return -1;
    }

    // Создание парсера для XML-схемы
    xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewParserCtxt(xsd_filename);
    if (parser_ctxt == NULL) {
        fprintf(stderr, "Unable to create XML schema parser context.\n");
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    // Загрузка XML-схемы
    xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
    if (schema == NULL) {
        fprintf(stderr, "Failed to parse XML schema.\n");
        xmlSchemaFreeParserCtxt(parser_ctxt);
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    // Создание контекста валидации
    xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
    if (valid_ctxt == NULL) {
        fprintf(stderr, "Unable to create XML schema validation context.\n");
        xmlSchemaFree(schema);
        xmlSchemaFreeParserCtxt(parser_ctxt);
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    if (xmlSchemaValidateDoc(valid_ctxt, xml_file) == 0) {
        cleanup(valid_ctxt, schema, parser_ctxt, xml_file);
        return 0;
    } else {
        cleanup(valid_ctxt, schema, parser_ctxt, xml_file);
        return 1;
    }
}

int validate_response_xml(const char *xml_content, const char *xsd_filename) {
    // Инициализация библиотеки libxml2
    xmlInitParser();

    // Загрузка XML-документа из строки
    xmlDocPtr xml_file = xmlReadMemory(xml_content, strlen(xml_content), "noname.xml", NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML content.\n");
        xmlCleanupParser();
        return -1;
    }

    // Создание парсера для XML-схемы
    xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewParserCtxt(xsd_filename);
    if (parser_ctxt == NULL) {
        fprintf(stderr, "Unable to create XML schema parser context.\n");
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    // Загрузка XML-схемы
    xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
    if (schema == NULL) {
        fprintf(stderr, "Failed to parse XML schema.\n");
        xmlSchemaFreeParserCtxt(parser_ctxt);
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    // Создание контекста валидации
    xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
    if (valid_ctxt == NULL) {
        fprintf(stderr, "Unable to create XML schema validation context.\n");
        xmlSchemaFree(schema);
        xmlSchemaFreeParserCtxt(parser_ctxt);
        xmlFreeDoc(xml_file);
        xmlCleanupParser();
        return -1;
    }

    if (xmlSchemaValidateDoc(valid_ctxt, xml_file) == 0) {
        cleanup(valid_ctxt, schema, parser_ctxt, xml_file);
        return 0;
    } else {
        cleanup(valid_ctxt, schema, parser_ctxt, xml_file);
        return 1;
    }
}