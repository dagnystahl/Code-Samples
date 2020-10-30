using System;
using System.Text.Json.Serialization;

namespace UserServices
{
    public class CanvasUser
    {
        [JsonPropertyName("id")]
        public int Id { get; set; }

        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("created_at")]
        public DateTime CreatedAt { get; set; }

        [JsonPropertyName("sortable_name")]
        public string SortableName { get; set; }

        [JsonPropertyName("short_name")]
        public string ShortName { get; set; }

        [JsonPropertyName("avatar_url")]
        public string AvatarUrl { get; set; }

        [JsonPropertyName("locale")]
        public object Locale { get; set; }

        [JsonPropertyName("effective_locale")]
        public string EffectiveLocale { get; set; }

        [JsonPropertyName("permissions")]
        public UserPermissions Permissions { get; set; }
    }
}