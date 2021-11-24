//
// Created by Tom Guy on 11/23/2021.
//

#include "PlayerManager.h"

namespace wet1_dast
{

    PlayerManager* PlayerManager::init()
    {
        try
        {
            auto* Manager = new PlayerManager();
            return Manager;
        }
        catch (const std::exception& e)
        {
        }
        return nullptr;
    }

    PlayerManager::StatusType PlayerManager::AddGroup(int GroupId)
    {
        if(GroupId <= 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group new_group(GroupId);
            Node new_node(&new_group);
            Groups.insert(new_node);
            Node* closest = Groups.findClosest(new_node);
            if(!closest)
            {
                non_empty_groups->next = &new_node;
            }
            else
            {
                if(*closest <= new_node)
                {
                    insertInLocation(closest, &new_node);
                }
                else
                {
                    insertInLocation(&new_node, closest);
                }
            }
        }
        catch {}
    }

     void PlayerManager::insertInLocation(Node* before, Node* after)
    {
        Node* temp = before->next;
        before->next = after;
        after->next = temp;
        after->prev = before;
        temp->prev = after;
        after->next_non_empty = before->next_non_empty;
        (before->group->GetSize() == 0) ? after->prev_non_empty = before->prev_non_empty : after->prev_non_empty = before;
    }
}