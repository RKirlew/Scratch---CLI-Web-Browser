#include "html_parser.h"
#include <stdio.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>

void parse_html(const char *html_content) {
    TidyDoc tdoc = tidyCreate();
    TidyBuffer output = {0};

    tidyParseString(tdoc, html_content);
    tidyCleanAndRepair(tdoc);
    tidyRunDiagnostics(tdoc);
    tidySaveBuffer(tdoc, &output);

    printf("Parsed and tidied HTML content:\n%s\n", output.bp);

    tidyBufFree(&output);
    tidyRelease(tdoc);
}

