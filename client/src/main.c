#include "../include/parser.h"
#include "../include/view.h"
#include "../include/client.h"
#include "../../schema/xml_validator.c"

void free_request(struct request *request) {
    if (request->attributes) {
        struct attribute *attribute;
        while (request->attributes) {
            attribute = request->attributes;
            request->attributes = attribute->next_attribute;
            free(attribute);
        }
    }
    if (request->operation) free(request->operation);
    if (request->parent_id) free(request->parent_id);
    if (request->star) free(request->star);
    free(request);
}

int main(int argc, char **argv) {

    const char *xsd_filename = "../../schema/request.xsd";
    while (1) {

        int size_tree;
        xmlDocPtr request_tree;

        printf("enter your request\n");

        char req[MAX_REQUEST_SIZE];
        fgets(req, MAX_REQUEST_SIZE, stdin);

        struct request *request = malloc(sizeof(struct request));
        enum parser_status status = parse_request(req, request);
        if (status != PARSE_OK) {
            printf("Request error\n");
            exit(status);
        }

        //get_request_view(request);

        request_tree = xmlNewDoc(BAD_CAST "1.0");
        int validate_result = validate_request_xml(request_tree, &xsd_filename);

        status = get_xml(request, request_tree);
        xmlChar *str_tree = (xmlChar *) malloc(sizeof(xmlChar) * MAX_REQUEST_SIZE);
        xmlDocDumpMemory(request_tree, &str_tree, &size_tree);

        printf("%s\n", (char *) str_tree);

        if (status == WRAP_OK && !validate_result) sendRequest(atoi(argv[1]), size_tree, (char *) str_tree);

        free(str_tree);
        free_request(request);
    }

    return 0;
}