#include "../cs225/catch/catch.hpp"
#include "../reddit.h"

using namespace reddit;

TEST_CASE("Small data is correctly parsed into a graph", "[parsedata]") {
    Reddit r;
    r.parseData("data/small_data.tsv");
    Graph g = r.getGraph();
    REQUIRE(g.vertexExists("leagueoflegends"));
    REQUIRE(g.vertexExists("teamredditteams"));
    REQUIRE(g.edgeExists("leagueoflegends", "teamredditteams"));

    REQUIRE(g.vertexExists("theredlion"));
    REQUIRE(g.vertexExists("soccer"));
    REQUIRE(g.edgeExists("theredlion", "soccer"));

    REQUIRE(g.vertexExists("inlandempire"));
    REQUIRE(g.vertexExists("bikela"));
    REQUIRE(g.edgeExists("inlandempire", "bikela"));

    REQUIRE(g.vertexExists("nfl"));
    REQUIRE(g.vertexExists("cfb"));
    REQUIRE(g.edgeExists("nfl", "cfb"));

    REQUIRE(g.vertexExists("playmygame"));
    REQUIRE(g.vertexExists("gamedev"));
    REQUIRE(g.edgeExists("playmygame", "gamedev"));

    REQUIRE(g.vertexExists("dogemarket"));
    REQUIRE(g.vertexExists("dogecoin"));
    REQUIRE(g.edgeExists("dogemarket", "dogecoin"));
}

TEST_CASE("Connected components are divided correctly", "[pagerank]") {
    Reddit r;
    r.parseData("data/mult_connected.tsv");
    r.pagerank();
    std::vector<std::vector<Vertex>> connected_comp = r.getConnectedComponents();
    std::vector<std::vector<Vertex>> actual_comp = {
        {"leagueoflegends",	"teamredditteams", "inlandempire"},
        {"playmygame", "gamedev", "dogemarket", "dogecoin", "nfl", "cfb", "fakereddit"}
    };

    for (unsigned int i = 0; i < connected_comp.size(); i++) {
        std::sort(connected_comp[i].begin(), connected_comp[i].end());
        std::sort(actual_comp[i].begin(), actual_comp[i].end());
    }

    std::sort(connected_comp.begin(), connected_comp.end());
    std::sort(actual_comp.begin(), actual_comp.end());

    REQUIRE(connected_comp == actual_comp);
}
