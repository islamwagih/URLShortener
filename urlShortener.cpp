#include <iostream>
#include <map>

//one to one mapping 
class URLShortener
{
private:
	#define SHORT_LINK_LENGTH 6 // length of the shortened length
	long long nextShortLinkID; // next id to be used to generate a unique 6 character short link
	std::map<std::string, std::string> longLinkDB;// maps long link to the shortener one
	std::map<std::string, std::string> shortLinkDB;// maps short link to the original(long) link
	std::map<int, char> base62;// maps base 10 to base 62 value
	void generateUniqueShortLink(std::string url)
	{
		//convert id to the base62
		std::string shortLink = base10ToBase62(nextShortLinkID);
		//increase the id by one to generate a unique one next time
		nextShortLinkID++;
		longLinkDB[url] = shortLink;
		shortLinkDB[shortLink] = url;
	}

	// convert base 10 to base 62 
	std::string base10ToBase62(long long id)
	{
	    std::string bs = "";
	    int base = 62;
	    while(id > base)
	    {
	        long double whole = (long double)id/base;
	        long double fraction = whole - (long long)whole;
	        bs += base62[fraction*base];
	        id = (long long)whole;
	    }
	    if(id > 0) bs += base62[id];
	    int left = 0, right = bs.size();
	    right--;
	    // reverse the string to be valid
	    while(left < right) std::swap(bs[left++], bs[right--]);
	    //enforce short link length
	    while(bs.size() < SHORT_LINK_LENGTH) bs+='0';
	    return bs;
	}


public:
	URLShortener():nextShortLinkID(0)
	{
		//initialize base62 
		int nextValue = 0;
		for(char i='0';i<='9';i++)
		{
			base62[nextValue++] = i;
		}

		for(char i='A';i<='Z';i++)
		{
			base62[nextValue++] = i; 
		}

		for(char i='a';i<='z';i++)
		{
			base62[nextValue++] = i;
		}
	}

	std::string shorten(std::string url) // shorten a give long url to a 6 alphanumeric characters short link
 	{
		//check if it's not exist create new one then return the short url
		if(longLinkDB.find(url) == longLinkDB.end())
		{
			generateUniqueShortLink(url);
		}
		return longLinkDB[url];
	}

	std::string restore(std::string url) //restore original link from the shorten one
	{
		// check if it's not exist 
		if(shortLinkDB.find(url) == shortLinkDB.end())
		{
			return "NO CORRESPONDING ORIGINAL LINK TO RESTORE"; //error invalid short url
		}
		// restore it
		return shortLinkDB[url];
	}

};


int main()
{
	URLShortener engine;
    std::cout<<engine.shorten("www.google.com")<<std::endl;
    std::cout<<engine.shorten("www.facebook.com")<<std::endl;

    int test = 1e3;

    for(int i=0;i<=test;i++)
    {
        std::string url = "";
        for(int j=0;j<=20;j++)
        {
            url += (rand()%26)+'a';

        }
        std::cout<<"random string = "<<url<<'\n';
        std::cout<<engine.shorten(url)<<'\n';
    }

    std::cout<<"========== MARGIN ==========\n";

    std::cout<<engine.restore("e00000")<<std::endl;
    std::cout<<engine.restore("1H0000")<<std::endl;

    std::cout<<engine.shorten("ubmjrmbsztsshfroefwsj")<<std::endl;
    std::cout<<engine.shorten("dzsxttobbgqngvvpjgojo")<<std::endl;

}