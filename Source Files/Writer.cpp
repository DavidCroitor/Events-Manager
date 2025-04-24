#include "Writer.h"

#include <utility>

Writer::Writer(std::string f, Repository &r) : filename(std::move(f)), repo(r) {}


HTMLWriter::HTMLWriter(std::string f, Repository &r) : Writer(std::move(f), r) {}

void HTMLWriter::writeToFile() {
    ofstream file(this->filename);
    if (file.is_open()) {
        file << "<!DOCTYPE html>\n"
                "<html>\n"
                "<head>\n"
                "   <title> EVENTS </title>\n"
                "</head>\n"
                "<body>\n"
                "<table border = \"1\">\n"
                "   <tr>\n"
                "       <td>Title</td>\n"
                "       <td>Description</td>\n"
                "       <td>Date and time</td>\n"
                "       <td>Number of people</td>\n"
                "       <td>Link</td>\n"
                "   </tr>\n";
        for (auto &event: this->repo.getUserEvents()) {
            file << "   <tr>\n";
            file << "       <td>" << event.getTitle() << "</td>\n";
            file << "       <td>" << event.getDescription() << "</td>\n";
            file << "       <td>" << event.getDateAndTime() << "</td>\n";
            file << "       <td>" << event.getNumberOfPeople() << "</td>\n";
            file << "       <td>" << "<a href=\"" << event.getLink() << "\">Link</a></td>\n";
            file << "   </tr>\n";
        }
        file << "</table>\n"
                "</body>\n"
                "</html>\n";
    }
    file.close();

}


CSVWriter::CSVWriter(std::string filename, Repository &repo) : Writer(std::move(filename), repo) {}

void CSVWriter::writeToFile() {
    ofstream file(this->filename);
    if (file.is_open()) {
        for (auto &event: this->repo.getUserEvents()) {
            file << event.getTitle() << "," << event.getDescription() << "," << event.getDateAndTime() << ","
                 << event.getNumberOfPeople() << "," << event.getLink() << "\n";
        }
    }
    file.close();
}
