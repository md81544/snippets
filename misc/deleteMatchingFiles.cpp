// REquires boost filesystem and regex

void DeleteMatchingFiles(
    const std::string& directory,
    const std::string& regexString
    )
{
    namespace fs = boost::filesystem;
    fs::path localDir(directory);
    fs::directory_iterator itEnd;
    const boost::regex rgx(regexString, boost::regex::icase);
    for (fs::directory_iterator it(localDir); it != itEnd; ++it)
    {
        auto file = (*it).path().filename().string();
        if (boost::regex_match(file, rgx))
        {
            fs::remove((*it).path());
        }
    }
}

