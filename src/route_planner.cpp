#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;
    start_node = &model.FindClosestNode(start_x, start_y);
    end_node = &model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*this->end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for (auto neighbor : current_node->neighbors) {
        if (!neighbor->visited) {
            neighbor->parent = current_node;
            neighbor->h_value = CalculateHValue(neighbor);
            neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
            neighbor->visited = true;
            open_list.push_back(neighbor);
        }
    }
}

RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(), [](const RouteModel::Node* a, const RouteModel::Node* b){
        const float sum_a = a->g_value + a->h_value;
        const float sum_b = b->g_value + b->h_value;
        return sum_a > sum_b;
    });

    RouteModel::Node * lowest = open_list.back();
    open_list.pop_back();
    return lowest;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node* node = current_node;

    while (node != this->start_node) {
        path_found.push_back(*node);
        distance += node->distance(*node->parent);
        node = node->parent;
    }

    path_found.push_back(*this->start_node);
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    std::reverse(path_found.begin(), path_found.end());
    return path_found;
}

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    current_node = this->start_node;
    current_node->visited = true;
    this->open_list.push_back(current_node);
    this->AddNeighbors(current_node);

    while (open_list.size() > 0) {
        current_node = NextNode();
        if (current_node == this->end_node) {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }
        this->AddNeighbors(current_node);
    }
}
