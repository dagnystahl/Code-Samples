using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace UserServices
{
    public interface ICanvasUserService
    {
        Task<CanvasUser> VerifyPersonalAccessTokenAsync(string token);
    }
}
