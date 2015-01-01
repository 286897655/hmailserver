// Copyright (c) 2005 Martin Knafve / hMailServer.com.  
// http://www.hmailserver.com
// Created 2005-07-21

#pragma once

#include "../Util/Singleton.h"
#include "../BO/Messages.h"

namespace HM
{

   class CachedMessages
   {
   public:
      
      CachedMessages(std::shared_ptr<Messages> messages) :
         messages_(messages),
         refresh_needed_(false)
      {
         
      }

      __int64 GetID()
      {
         return messages_->GetFolderID();
      }

      String GetName()
      {
         String name = Formatter::Format("{0}", messages_->GetAccountID());
         
         return name;
      }

      size_t GetEstimatedCachingSize()
      {
         return 1024 * messages_->GetCount();
      }

      std::shared_ptr<Messages> GetMessages() 
      { 
         if (refresh_needed_)
         {
            messages_->Refresh();
            refresh_needed_ = false;
         }

         return messages_; 
      }

      void SetRefreshNeeded()
      {
         refresh_needed_ = true;
      }

   private:

      std::shared_ptr<Messages> messages_;
      bool refresh_needed_;
   };
}