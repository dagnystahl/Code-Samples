using System.Text.Json.Serialization;

namespace UserServices
{
    public class UserPermissions
    {
        [JsonPropertyName("can_update_name")]
        public bool CanUpdateName { get; set; }

        [JsonPropertyName("can_update_avatar")]
        public bool CanUpdateAvatar { get; set; }

        [JsonPropertyName("limit_parent_app_web_access")]
        public bool LimitParentAppWebAccess { get; set; }
    }

}