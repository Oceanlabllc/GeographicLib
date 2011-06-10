function [latlong, aux] = geodesicline(lat1, lon1, azi1, distances, a, r)
%geodesicline  Compute points along a geodesic
%
%   [latlong, aux] = geodesicline(lat1, lon1, azi1, distances)
%   [latlong, aux] = geodesicline(lat1, lon1, azi1, distances, a, r)
%
%   lat1 is the latitude of point 1 (scalar) in degrees
%   lon1 is the longitude of point 1 (scalar) in degrees
%   azi1 is the azimuth at point 1 (scalar) in degrees
%   distances is an M x 1 vector of distances to point 2 in meters
%
%   latlong is an M x 3 matrix
%       latitude of point 2 = geodesic(:,1) in degrees
%       longitude of point 2 = geodesic(:,2) in degrees
%       azimuth at point 2 = geodesic(:,3) in degrees
%   aux is an M x 4 matrix
%       reduced length = aux(:,1) in meters
%       geodesic scale 1 to 2 = aux(:,2)
%       geodesic scale 2 to 1 = aux(:,3)
%       area under geodesic = aux(:,4) in meters^2
%
%   a = major radius (meters)
%   r = reciprocal flattening (0 means a sphere)
%   If a and r are omitted, the WGS84 values are used.
%
%   The result is the same as produced by
%       geodesicdirect([repmat([lat1, lon1, azi1],size(distances)), ...
%                       distances], a, r)
%
%   This is an interface to the GeographicLib C++ routine
%       GeodesicLine::Position
%   See the documentation on this function for more information.
  error('Error: executing .m file instead of compiled routine');
end
% geodesicline.m
% Matlab .m file for computing points along a geodesic
%
% Copyright (c) Charles Karney (2010, 2011) <charles@karney.com> and
% licensed under the LGPL.  For more information, see
% http://geographiclib.sourceforge.net/
%
% $Id$