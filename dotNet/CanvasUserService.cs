using CanvasCommon;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text.Json;
using System.Threading.Tasks;

namespace UserServices
{
    public class CanvasUserService : ICanvasUserService
    {
        private readonly CanvasOptions _options; //tell us the host
        private readonly ILogger<CanvasUserService> _logger;

        public CanvasUserService(IOptions<CanvasOptions> options, ILogger<CanvasUserService> logger)
        {
            _options = options.Value;
            _logger = logger;
        }
        //do async bc we're making a call
        public async Task<CanvasUser> VerifyPersonalAccessTokenAsync(string token)
        {
            string baseURL = _options.Host; //this is the base url like https://elearning.mines.edu...
            //create an http client and set its base url to use to make calls
            var client = new HttpClient() { BaseAddress = new System.Uri(baseURL) };
            var contentType = new MediaTypeWithQualityHeaderValue("application/json");
            client.DefaultRequestHeaders.Accept.Add(contentType);
            //put the bearer token into the header
            client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
            //make the call
            HttpResponseMessage response = await client.GetAsync($"/api/v1/users/self");
            if (response.IsSuccessStatusCode)
            {
                string stringData = await response.Content.ReadAsStringAsync();
                var user = JsonSerializer.Deserialize<CanvasUser>(stringData);
                return user;
            }

            _logger.LogError($"Failed to verify personal access token: [{token}]");
            throw new StatusCodeException(response.StatusCode);
        }
    }
}
